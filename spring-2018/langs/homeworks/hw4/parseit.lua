-- parseit.lua
-- William Horn
-- 16 Feb 2018

local parseit = {}

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

function shouldPrefOp(string_form, category)
    return category == lexit.ID or
    category == lexit.NUMLIT or
    string_form == "]" or
    string_form == ")" or
    string_form == "true" or
    string_form == "false"
end

local function advance()
    lexer_out_s, lexer_out_c = iter(state, lexer_out_s)

    if lexer_out_s ~= nil then
        if shouldPrefOp(lexer_out_s, lexer_out_c) then
            lexit.preferOp()
        end

        lexstr, lexcat = lexer_out_s, lexer_out_c
    else
        lexstr, lexcat = "", 0
    end
end

local function init(prog)
    iter, state, lexer_out_s = lexit.lex(prog)
    advance()
end

local function atEnd()
    return lexcat == 0
end

local function matchString(s)
    if lexstr == s then
        advance()
        return true
    else
        return false
    end
end

local function matchCat(c)
    if lexcat == c then
        advance()
        return true
    else
        return false
    end
end

function parseit.parse(prog)
    init(prog)

    local good, ast = parse_program()
    local done = atEnd()

    return good, done, ast
end

function parse_program()
    local good, ast

    good, ast = parse_stmt_list()
    return good, ast
end

function parse_stmt_list()
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

function parse_statement()
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
    local id, ast1

    id = lexstr
    if matchCat(lexit.ID) then
        if matchString("[") then
            good, ast1 = parse_expr()

            if not good then
                return false, nil
            end

            if matchString(']') then
                return true, { ARRAY_VAR, id, ast1 }
            end

            return false, nil
        else
            return true, { SIMPLE_VAR, id }
        end
    else
        return false, nil
    end
end

function parse_print_arg()
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

function parse_expr()
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
            if not matchString("==") and
                not matchString("!=") and
                not matchString("<") and
                not matchString("<=") and
                not matchString(">") and
                not matchString(">=") then
                break
            end

            good, ast2 = parse_arith_expr()
            if not good then
                return false, nil
            end

            ast = { { BIN_OP, saveop }, ast, ast2 }
        end

        return true, ast
    end
end

function parse_arith_expr()
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
    local savelex, good, ast, ast2
    savelex = lexstr

    if matchString("(") then
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
        return true, { NUMLIT_VAL, savelex }
    elseif matchString("true") or matchString("false") then
        return true, { BOOLLIT_VAL, savelex }
    else
        good, ast = parse_lvalue()
        if not good then
            return false, nil
        end

        return true, ast
    end
end

return parseit
