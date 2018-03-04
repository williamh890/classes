-- rdparser4.lua
-- Glenn G. Chappell
-- 16 Feb 2018


local parseit = {}  -- Our module

lexer = require "lexit"


-- Variables

-- For lexer iteration
local iter          -- Iterator returned by lexer.lex
local state         -- State for above iterator (maybe not used)
local lexer_out_s   -- Return value #1 from above iterator
local lexer_out_c   -- Return value #2 from above iterator

-- For current lexeme
local lexstr = ""   -- String form of current lexeme
local lexcat = 0    -- Category of current lexeme:
                    --  one of categories below, or 0 for past the end

-- Symbolic Constants for AST

-- BIN_OP = 1
-- NUMLIT_VAL = 2
-- SIMPLE_VAR = 3

STMT_LIST   = 1
INPUT_STMT  = 2
PRINT_STMT  = 3
FUNC_STMT   = 4
CALL_FUNC   = 5
IF_STMT     = 6
WHILE_STMT  = 7
ASSN_STMT   = 8
CR_OUT      = 9
STRLIT_OUT  = 10
BIN_OP      = 11
UN_OP       = 12
NUMLIT_VAL  = 13
BOOLLIT_VAL = 14
SIMPLE_VAR  = 15
ARRAY_VAR   = 16



-- Utility Functions
function shouldPrefOp(string_form, category)
    return category == ID or
    category == NUMLIT or
    string_form == "]" or
    string_form == ")" or
    string_form == "true" or
    string_form == "false"
end

-- advance
-- Go to next lexeme and load it into lexstr, lexcat.
-- Should be called once before any parsing is done.
-- Function init must be called before this function is called.
local function advance()
    -- Advance the iterator
    lexer_out_s, lexer_out_c = iter(state, lexer_out_s)

    -- If we're not past the end, copy current lexeme into vars
    if lexer_out_s ~= nil then
        lexstr, lexcat = lexer_out_s, lexer_out_c

        if shouldPrefOp(lexstr, lexcat) then
            lexit.preferOp()
        end
    else
        lexstr, lexcat = "", 0
    end
end

-- init
-- Initial call. Sets input for parsing functions.
local function init(prog)
    iter, state, lexer_out_s = lexer.lex(prog)
    advance()
end

-- atEnd
-- Return true if pos has reached end of input.
-- Function init must be called before this function is called.
local function atEnd()
    return lexcat == 0
end

-- matchString
-- Given string, see if current lexeme string form is equal to it. If
-- so, then advance to next lexeme & return true. If not, then do not
-- advance, return false.
-- Function init must be called before this function is called.
local function matchString(s)
    if lexstr == s then
        advance()
        return true
    else
        return false
    end
end

-- matchCat
-- Given lexeme category (integer), see if current lexeme category is
-- equal to it. If so, then advance to next lexeme & return true. If
-- not, then do not advance, return false.
-- Function init must be called before this function is called.
local function matchCat(c)
    if lexcat == c then
        advance()
        return true
    else
        return false
    end
end

-- Primary Function for Client Code

function parseit.parse(prog)
    -- Initialization
    init(prog)

    -- Get results from parsing
    local good, ast = parse_statement_list()  -- Parse start symbol
    local done = atEnd()

    -- And return them
    return good, done, ast
end

function is_statement_start_keyword()
    return matchString('input') or
    matchString('print') or
    matchString('func') or
    matchString('call') or
    matchString('if') or
    matchString('while')
end

function parse_statement_list()
    local good, ast, newast

    good, ast = parse_statement()
    if not good then
        return false, nil
    end
    ast = {STMT_LIST, ast}

    while true do
        if not is_statement_start_keyword() then
            break
        end

        good, statement = parse_statement()
        if not good then
            return false, nil
        end
    end

    return true, ast
end

function parse_statement()
    return true, nil
end


function parse_expr()
    local good, ast, saveop, newast

    good, ast = parse_term()
    if not good then
        return false, nil
    end

    while true do
        saveop = lexstr
        if not matchString("+") and not matchString("-") then
            break
        end

        good, newast = parse_term()
        if not good then
            return false, nil
        end

        ast = { { BIN_OP, saveop }, ast, newast }
    end

    return true, ast
end

function parse_term()
    local good, ast, saveop, newast

    good, ast = parse_factor()
    if not good then
        return false, nil
    end

    while true do
        saveop = lexstr
        if not matchString("*") and not matchString("/") then
            break
        end

        good, newast = parse_factor()
        if not good then
            return false, nil
        end

        ast = { { BIN_OP, saveop }, ast, newast }
    end

    return true, ast
end

function parse_factor()
    local savelex, good, ast

    savelex = lexstr
    if matchCat(lexer.ID) then
        return true, { SIMPLE_VAR, savelex }
    elseif matchCat(lexer.NUMLIT) then
        return true, { NUMLIT_VAL, savelex }
    elseif matchString("(") then
        good, ast = parse_expr()
        if not good then
            return false, nil
        end

        if not matchString(")") then
            return false, nil
        end

        return true, ast
    else
        return false, nil
    end
end


return parseit

