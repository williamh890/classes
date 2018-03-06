-- rdparser4.lua
-- Glenn G. Chappell
-- 16 Feb 2018


local parseit = {}  -- Our module

lexit = require "lexit"

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

local STMT_LIST   = 1
local INPUT_STMT  = 2
local PRINT_STMT  = 3
local FUNC_STMT   = 4
local CALL_FUNC   = 5
local IF_STMT     = 6
local WHILE_STMT  = 7
local ASSN_STMT   = 8
local CR_OUT      = 9
local STRLIT_OUT  = 10
local BIN_OP      = 11
local UN_OP       = 12
local NUMLIT_VAL  = 13
local BOOLLIT_VAL = 14
local SIMPLE_VAR  = 15
local ARRAY_VAR   = 16

-- Utility Functions
function shouldPrefOp(string_form, category)
    return category == lexit.ID or
    category == lexit.NUMLIT or
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
        if not shouldPrefOp(lexer_out_s, lexer_out_c) then
            lexit.preferOp()
        end

        lexstr, lexcat = lexer_out_s, lexer_out_c
    else
        lexstr, lexcat = "", 0
    end
end

-- init
-- Initial call. Sets input for parsing functions.
local function init(prog)
    iter, state, lexer_out_s = lexit.lex(prog)
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
    local good, ast = parse_program()  -- Parse start symbol
    local done = atEnd()

    -- And return them
    return good, done, ast
end

-- parse_program
-- Parsing function for nonterminal "program".
-- Function init must be called before this function is called.
function parse_program()
    local good, ast

    good, ast = parse_stmt_list()
    return good, ast
end


-- parse_stmt_list
-- Parsing function for nonterminal "stmt_list".
-- Function init must be called before this function is called.
function parse_stmt_list()
    -- print("PARSING STMT LIST")
    local good, ast, newast

    ast = { STMT_LIST }
    while true do
        if lexstr ~= "input"
          and lexstr ~= "print"
          and lexstr ~= "func"
          and lexstr ~= "call"
          and lexstr ~= "if"
          and lexstr ~= "while"
          and lexcat ~= lexit.ID then
            return true, ast
        end

        good, newast = parse_statement()
        if not good then
            return false, nil
        end

        table.insert(ast, newast)
    end
end


-- parse_statement
-- Parsing function for nonterminal "statement"
-- Function init must be called before this function is called.
function parse_statement()
    -- print("PARSING STMT")
    local good, ast1, ast2, savelex

    if matchString("input") then
        good, ast1 = parse_lvalue()
        if not good then
            return false, nil
        end

        return true, { INPUT_STMT, ast1 }

    elseif matchString("print") then
        good, ast1 = parse_print_arg()
        if not good then
            return false, nil
        end

        ast2 = { PRINT_STMT, ast1 }

        while true do
            if not matchString(";") then
                break
            end

            good, ast1 = parse_print_arg()
            if not good then
                return false, nil
            end

            table.insert(ast2, ast1)
        end

        return true, ast2

    elseif matchString("func") then
        savelex = lexstr
        if not matchCat(lexit.ID) then
            return false, nil
        end

        good, ast1 = parse_stmt_list()
        if not good then
            return false, nil
        end

        if matchString('end') then
            return true, { FUNC_STMT, savelex, ast1 }
        end

        return false, ast1

    elseif matchString("call") then
        local savelex = lexstr
        if not matchCat(lexit.ID) then
            return false, nil
        end

        return true, { CALL_FUNC, savelex }
    elseif matchString("if") then
        -- print("IF")
        local if_total_ast = { IF_STMT }
        good, ast1 = parse_expr()
        if not good then
            return false, nil
        end

        good, ast2 = parse_stmt_list()
        if not good then
            return false, nil
        end

        table.insert(if_total_ast, ast1)
        table.insert(if_total_ast, ast2)

        while true do
            if not matchString('elseif') then
                break
            end
            -- print("ELSEIF")

            good, ast1 = parse_expr()
            if not good then
                return false, nil
            end

            good, ast2 = parse_stmt_list()
            if not good then
                return false, nil
            end

            table.insert(if_total_ast, ast1)
            table.insert(if_total_ast, ast2)
        end

        local else_ast
        if matchString('else') then
            -- print("ELSE")
            good, else_ast = parse_stmt_list()
            if not good then
                return false, nil
            end
            table.insert(if_total_ast, else_ast)
            if matchString('end') then
                return true, if_total_ast
            end

            return false, if_total_ast
        end

        if matchString('end') then
            return true, if_total_ast
        end

        return false, if_total_ast
    elseif matchString("while") then
        good, ast1 = parse_expr()
        if not good then
            return false, nil
        end

        good, ast2 = parse_stmt_list()
        if not good then
            return false, nil
        end

        if matchString('end') then
            return true, { WHILE_STMT, ast1, ast2 }
        end

        return false, { ast1, ast2 }
    else
        good, ast1 = parse_lvalue()
        if not good then
            return false, nil
        end

        if not matchString("=") then
            return false, ast1
        end

        good, ast2 = parse_expr()
        if not good then
            return false, nil
        end

        return true, { ASSN_STMT, ast1, ast2 }
    end
end

function parse_lvalue()
    -- print("PARSING LVALUE")
    local id, ast1

    id = lexstr
    if matchCat(lexit.ID) then
        if matchString("[") then
            -- print("PARSE ARR")
            good, ast1 = parse_expr()

            if not good then
                return false, nil
            end

            if matchString(']') then
                return true, { ARRAY_VAR, id, ast1 }
            end

            return false, nil
        else
            -- print("PARSE SIMPLE")
            return true, { SIMPLE_VAR, id }
        end
    else
        return false, nil
    end
end

function parse_print_arg()
    -- print( "PARSING PRINT ARG" )
    local savelex, ast, good
    savelex = lexstr

    if matchString('cr') then
        return true, { CR_OUT }
    elseif matchCat(lexit.STRLIT) then
        return true, { STRLIT_OUT, savelex }
    else
        good, ast = parse_expr()
        if not good then
            return false, nil
        end

        return true, ast
    end
end

function is_not_logical_bin_op()
    return
end

function is_not_arithmetic_bin_op()
    return
end

function parse_expr()
    -- print("PARSE EXPRESSION", lexstr)
    local good, ast, saveop, newast

    good, ast = parse_comp_expr()
    if not good then
        return false, nil
    end

    while true do
        saveop = lexstr
        if not matchString("&&") and not matchString("||") then
            break
        end

        good, newast = parse_comp_expr()
        if not good then
            return false, nil
        end

        ast = { { BIN_OP, saveop }, ast, newast }
    end

    return true, ast
end

function parse_comp_expr()
    -- print("PARSE COMP EXPR", lexstr)
    local good, ast, ast2, saveop

    if matchString("!") then
        good, ast = parse_comp_expr()
        if not good then
            return false, nil
        end

        return true, { { UN_OP, "!" } , ast }
    else
        good, ast = parse_arith_expr()
        if not good then
            return false, nil
        end

        while true do
            saveop = lexstr
            -- io.write("In comp exper while with ", saveop)
            if not matchString("==") and
                not matchString("!=") and
                not matchString("<") and
                not matchString("<=") and
                not matchString(">") and
                not matchString(">=") then
                break
            end
            -- io.write(" ... didn't break\n")

            good, ast2 = parse_arith_expr()
            if not good then
                return false, nil
            end

            ast = { { BIN_OP, saveop }, ast, ast2 }
        end
        -- io.write(" ... broke \n")

        return true, ast
    end
end

function parse_arith_expr()
    -- print("PARSE ARITH EXPR", lexstr)
    local good, ast, ast2, saveop

    good, ast = parse_term()
    if not good then
        return false, nil
    end

    while true do
        saveop = lexstr
        if not matchString("+") and not matchString("-") then
            break
        end

        good, ast2 = parse_term()
        if not good then
            return false, nil
        end

        ast = { { BIN_OP, saveop }, ast, ast2 }
    end

    return true, ast
end

function parse_term()
    -- print("TERM", lexstr)
    local good, ast, saveop, newast

    good, ast = parse_factor()
    if not good then
        return false, nil
    end

    while true do
        saveop = lexstr
        if not matchString("*") and not matchString("/") and not matchString("%") then
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
    -- print("FACTOR", lexstr)
    local savelex, good, ast, ast2
    savelex = lexstr

    if matchString("(") then
        -- print("expression")
        good, ast = parse_expr()
        if not good then
            return false, nil
        end

        if not matchString(")") then
            return false, nil
        end

        return true, ast
    elseif matchString("+") or matchString("-") then
        local op = savelex
        good, ast2 = parse_factor()
        if not good then
            return false, nil
        end

        return true, {{ UN_OP, op }, ast2}
    elseif matchString("call") then
        savelex = lexstr
        if matchCat(lexit.ID) then
            return true, { CALL_FUNC, savelex }
        else
            return false, nil
        end
    elseif matchCat(lexit.NUMLIT) then
        -- print("num lit")
        return true, { NUMLIT_VAL, savelex }
    elseif matchString("true") or matchString("false") then
        return true, { BOOLLIT_VAL, savelex }
    else
        -- print("lvalue")
        good, ast = parse_lvalue()
        if not good then
            return false, nil
        end

        return true, ast
    end
end


return parseit

