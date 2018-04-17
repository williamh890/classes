-- interpit.lua
-- William Horn
-- 4/17/18
--
-- For CS F331 / CSCE A331 Spring 2018
-- Interpret AST from parseit.parse
-- For Assignment 6, Exercise B


local interpit = {}  -- Our module

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

local function numToInt(n)
    assert(type(n) == "number")

    if n >= 0 then
        return math.floor(n)
    else
        return math.ceil(n)
    end
end


-- strToNum
-- Given a string, attempt to interpret it as an integer. If this
-- succeeds, return the integer. Otherwise, return 0.
local function strToNum(s)
    assert(type(s) == "string")

    -- Try to do string -> number conversion; make protected call
    -- (pcall), so we can handle errors.
    local success, value = pcall(function() return 0+s end)

    -- Return integer value, or 0 on error.
    if success then
        return numToInt(value)
    else
        return 0
    end
end


-- numToStr
-- Given a number, return its string form.
local function numToStr(n)
    assert(type(n) == "number")

    return ""..n
end


-- boolToInt
-- Given a boolean, return 1 if it is true, 0 if it is false.
local function boolToInt(b)
    assert(type(b) == "boolean")

    if b then
        return 1
    else
        return 0
    end
end

local function strToBool(str)
	assert(type(str) == "string")

    return str == "true"
end

-- astToStr
-- Given an AST, produce a string holding the AST in (roughly) Lua form,
-- with numbers replaced by names of symbolic constants used in parseit.
-- A table is assumed to represent an array.
-- See the Assignment 4 description for the AST Specification.
--
-- THIS FUNCTION IS INTENDED FOR USE IN DEBUGGING ONLY!
-- IT SHOULD NOT BE CALLED IN THE FINAL VERSION OF THE CODE.
function astToStr(x)
    local symbolNames = {
        "STMT_LIST", "INPUT_STMT", "PRINT_STMT", "FUNC_STMT",
        "CALL_FUNC", "IF_STMT", "WHILE_STMT", "ASSN_STMT", "CR_OUT",
        "STRLIT_OUT", "BIN_OP", "UN_OP", "NUMLIT_VAL", "BOOLLIT_VAL",
        "SIMPLE_VAR", "ARRAY_VAR"
    }
    if type(x) == "number" then
        local name = symbolNames[x]
        if name == nil then
            return "<Unknown numerical constant: "..x..">"
        else
            return name
        end
    elseif type(x) == "string" then
        return '"'..x..'"'
    elseif type(x) == "boolean" then
        if x then
            return "true"
        else
            return "false"
        end
    elseif type(x) == "table" then
        local first = true
        local result = "{"
        for k = 1, #x do
            if not first then
                result = result .. ","
            end
            result = result .. astToStr(x[k])
            first = false
        end
        result = result .. "}"
        return result
    elseif type(x) == "nil" then
        return "nil"
    else
        return "<"..type(x)..">"
    end
end

function interpit.interp(ast, state, incall, outcall)
	function interp_stmt_list(ast)
		for i = 2, #ast do
			interp_stmt(ast[i])
		end
	end

	function interp_stmt(ast)
		local lvalue, stringCat
        local statementType = ast[1]

		if statementType == INPUT_STMT then
            interp_input(ast[2])
		elseif statementType == PRINT_STMT then
            interp_print(ast)
		elseif statementType == FUNC_STMT then
            interp_func(ast)
		elseif statementType == CALL_FUNC then
            interp_call(ast)
		elseif statementType == IF_STMT then
            interp_if(ast)
		elseif statementType == WHILE_STMT then
            interp_while(ast)
		else
			assert(statementType == ASSN_STMT)
			rvalue = interp_expr(ast[3])
			interp_lvalue(ast[2], rvalue)
		end
	end

    function interp_input(ast)
        if ast[1] == SIMPLE_VAR then
            local lvalue = ast[2]
            local rvalue = incall()
            state.v[lvalue] = numToInt(strToNum(rvalue))
        end
    end

    function interp_print(ast)
        for i = 2, #ast do
            if ast[i][1] == CR_OUT then
                outcall("\n")
            elseif ast[i][1] == STRLIT_OUT then
                str = ast[i][2]
                outcall(str:sub(2,str:len()-1))
            else
                rvalue = interp_expr(ast[2])
                outcall(numToStr(rvalue))
            end
        end
    end

    function interp_func(ast)
        lvalue = ast[2]
        rvalue = ast[3]

        state.f[lvalue] = rvalue
    end

    function interp_call(ast)
        lvalue = ast[2]
        rvalue = state.f[lvalue]

        if rvalue == nil then
            rvalue = { STMT_LIST }
        end

        interp_stmt_list(rvalue)
    end

    function interp_if(ast)
        local done = false
        local elseIndex = 0

        for i=2, #ast-1, 2 do
            if interp_expr(ast[i]) ~= 0 and not done then
                interp_stmt_list(ast[i+1])
                done = true
            end

            elseIndex = i
        end

        if ast[elseIndex+2] ~= nil and not done then
            interp_stmt_list(ast[elseIndex+2])
        end
    end

    function interp_while(ast)
        while interp_expr(ast[2]) ~= 0 do
            interp_stmt_list(ast[3])
        end
    end

	function interp_lvalue(ast, rvalue)
		local lvalue

		if ast[1] == SIMPLE_VAR then
			lvalue = ast[2]

			state.v[lvalue] = numToInt(rvalue)

		elseif ast[1] == ARRAY_VAR then
			lvalue = ast[2]

			if state.a[lvalue] == nil then
                state.a[lvalue] = {}
            end

			state.a[lvalue][interp_expr(ast[3])] = rvalue
		end
	end

	function interp_expr(ast)
		local value;

		if ast[1] == NUMLIT_VAL then
			value = strToNum(ast[2])

		elseif ast[1] == SIMPLE_VAR then
			value = state.v[ast[2]]

		elseif ast[1] == ARRAY_VAR then
			if state.a[ast[2]] ~= nil then
				value = state.a[ast[2]][interp_expr(ast[3])]
			else
				value = 0
			end

		elseif ast[1] == BOOLLIT_VAL then
			value = boolToInt(strToBool(ast[2]))

		elseif ast[1] == CALL_FUNC then
			interp_stmt(ast)
			value = state.v["return"]

		elseif type(ast[1]) == "table" then
            value = interp_table(ast)
		end

		if value == nil then
            return 0
		else
            return value
		end
	end

    function interp_table(ast)
        local value
        if ast[1][1] == UN_OP then
            local operand = interp_expr(ast[2])

            value = interp_un_op(ast[1], operand)

        elseif ast[1][1] == BIN_OP then
            local lhs = interp_expr(ast[2])
            local rhs = interp_expr(ast[3])

            value = interp_bin_op(ast[1], lhs, rhs)

        end

        return value
    end

    function interp_un_op(ast, operand)
        local value

        if ast[2] == "+" then
            value = operand
        elseif ast[2] == "-" then
            value = -(operand)
        else
            if operand == 0 then
                value = 1
            else
                value = 0
            end
        end

        return value
    end

    function interp_bin_op(ast, lhs, rhs)
        local op = ast[2]
        local isEq = lhs == rhs
        local value


        if op == "+" then
            value = lhs + rhs
        elseif op == "-" then
            value = lhs - rhs
        elseif op == "*" then
            value = lhs * rhs
        elseif op == "/" then
            if rhs == 0 then
                value = rhs
            else
                value = numToInt(lhs / rhs)
            end
        elseif op == "%" then
            if rhs == 0 then
                value = rhs
            else
                value = numToInt(lhs % rhs)
            end
        elseif op == "==" then
            value = boolToInt(lhs == rhs)
        elseif op == "!=" then
            value = boolToInt(lhs ~= rhs)
        elseif op == "<=" then
            value = boolToInt(lhs <= rhs)
        elseif op == ">=" then
            value = boolToInt(lhs >= rhs)
        elseif op == "<" then
            value = boolToInt(lhs < rhs)
        elseif op == ">" then
            value = boolToInt(lhs > rhs)
        elseif op == "&&" then
            if lhs == 0 and rhs == 0 then
                value = 0
            elseif isEq then
                value = boolToInt(isEq)
            else
                value = boolToInt(isEq)
            end
        elseif op == "||" then
            if lhs == 0 and rhs == 0 then
                value = 0
            elseif lhs ~= 0 or rhs ~= 0 then
                value = 1
            elseif isEq then
                value = boolToInt(isEq)
            end
        end

        return value
    end

    interp_stmt_list(ast)

    return state
end

return interpit
