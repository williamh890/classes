-- lexir.lua
-- William Horn
-- 6 Feb 2018

local lexit = {}

lexit.KEY = 1
lexit.ID = 2
lexit.NUMLIT = 3
lexit.STRLIT = 4
lexit.OP = 5
lexit.PUNCT = 6
lexit.MAL = 7

-- catnames
lexit.catnames = {
    "Keyword",
    "Identifier",
    "NumericLiteral",
    "StringLiteral",
    "Operator",
    "Punctuation",
    "Malformed"
}


-- *********************************************************************
-- Kind-of-Character Functions
-- *********************************************************************

-- All functions return false when given a string whose length is not
-- exactly 1.


-- isLetter
-- Returns true if string c is a letter character, false otherwise.
local function isLetter(c)
    if c:len() ~= 1 then
        return false
    elseif c >= "A" and c <= "Z" then
        return true
    elseif c >= "a" and c <= "z" then
        return true
    else
        return false
    end
end


-- isDigit
-- Returns true if string c is a digit character, false otherwise.
local function isDigit(c)
    if c:len() ~= 1 then
        return false
    elseif c >= "0" and c <= "9" then
        return true
    else
        return false
    end
end


-- isWhitespace
-- Returns true if string c is a whitespace character, false otherwise.
local function isWhitespace(c)
    if c:len() ~= 1 then
        return false
    elseif c == " " or c == "\t" or c == "\n" or c == "\r"
      or c == "\f" then
        return true
    else
        return false
    end
end


-- isIllegal
-- Returns true if string c is an illegal character, false otherwise.
local function isIllegal(c)
    if c:len() ~= 1 then
        return false
    elseif isWhitespace(c) then
        return false
    elseif c >= " " and c <= "~" then
        return false
    else
        return true
    end
end


-- *********************************************************************
-- The Lexer
-- *********************************************************************

local preferOpFlag = false

function lexit.preferOp()
    preferOpFlag = true
end

-- lex
-- Our lexer
-- Intended for use in a for-in loop:
--     for lexstr, cat in lexer.lex(program) do
-- Here, lexstr is the string form of a lexeme, and cat is a number
-- representing a lexeme category. (See Public Constants.)
function lexit.lex(program)
    -- ***** Variables (like class data members) *****

    local pos               -- Index of next character in program
                            -- INVARIANT: when getLexeme is called, pos is
                            --  EITHER the index of the first character of the
                            --  next lexeme OR program:len()+1
    local state             -- Current state for our state machine
    local ch                -- Current character
    local lexstr            -- The lexeme, so far
    local category          -- Category of lexeme, set when state set to DONE
    local handlers          -- Dispatch table; value created later
    local stringQuoteType   -- Current type of quotes being used in string literal

    -- ***** States *****

    local DONE = 0
    local START = 1
    local LETTER = 2
    local DIGIT = 3
    local PLUS = 4
    local MINUS = 5
    local OP = 6
    local EXPONENT = 7
    local EXP_AFTER_PLUS = 8
    local STRLIT = 9

    -- ***** Character-Related Utility Functions *****

    local function currChar()
        return program:sub(pos, pos)
    end

    local function nextChar()
        return program:sub(pos+1, pos+1)
    end

    local function nextnextChar()
        return program:sub(pos+2, pos+2)
    end

    local function drop1()
        pos = pos+1
    end

    local function add1()
        lexstr = lexstr .. currChar()
        drop1()
    end

    local function removeComment()
        while true do
            if currChar() == "\n" then
                drop1()
                break
            elseif currChar() == "" then
                return
            end

            drop1()
        end
    end

    local function skipWhitespace()
        while true do
            while isWhitespace(currChar()) do
                drop1()
            end

            if currChar() ~= "#" then
                break
            end

            drop1()
            removeComment()
        end
    end

    local function isKeyword(str)
        return
            str == "call"       or
            str == "cr"         or
            str == "else"       or
            str == "elseif"     or
            str == "end"        or
            str == "false"      or
            str == "func"       or
            str == "if"         or
            str == "input"      or
            str == "print"      or
            str == "true"       or
            str == "while"
    end

    local function isStartOfExponent()
        return (ch == "e" or ch == "E") and
               (isDigit(nextChar()) or nextChar() == "+" and isDigit(nextnextChar()))
    end

    -- ***** State-Handler Functions *****

    local function handle_DONE()
        io.write("ERROR: 'DONE' state should not be handled\n")
        assert(0)
    end

    -- ops: = && || ! == != < <= > >= + - * / % [ ] ;
    local function isStartOfOp(char)
        return
            char == "*" or
            char == "/" or
            char == "=" or
            char == "&" or
            char == "|" or
            char == "!" or
            char == "<" or
            char == ">" or
            char == "%" or
            char == "[" or
            char == "]" or
            char == ";"
    end

    -- ops: = && || ! == != < <= > >= + - * / % [ ] ;
    local function isDoubleOp(testOp)
        return
            testOp == "&&" or
            testOp == "||" or
            testOp == "!=" or
            testOp == "==" or
            testOp == "<=" or
            testOp == ">="
    end

    -- ops: = ! < > + - * / % [ ] ;
    local function isOp(testOp)
        return
            testOp == "=" or
            testOp == "!" or
            testOp == ">" or
            testOp == "<" or
            testOp == "+" or
            testOp == "-" or
            testOp == "/" or
            testOp == "*" or
            testOp == "%" or
            testOp == "[" or
            testOp == "]" or
            testOp == ";"
    end

    local function handle_START()
        add1()

        if isIllegal(ch) then
            state = DONE
            category = lexit.MAL
        elseif isLetter(ch) or ch == "_" then
            state = LETTER
        elseif isDigit(ch) then
            state = DIGIT
        elseif ch == "+" then
            state = PLUS
        elseif ch == "-" then
            state = MINUS
        elseif isStartOfOp(ch) then
            state = OP
        elseif ch == '"' or ch == "'" then
            stringQuoteType = ch
            state = STRLIT
        else
            state = DONE
            category = lexit.PUNCT
        end
    end

    local function handle_LETTER()
        if isLetter(ch) or isDigit(ch) or ch == "_" then
            add1()
        else
            state = DONE
            if isKeyword(lexstr) then
                category = lexit.KEY
            else
                category = lexit.ID
            end
        end
    end

    local function handle_DIGIT()
        if isDigit(ch) then
            add1()
        elseif isStartOfExponent() then
            add1()
            state = EXPONENT
        else
            state = DONE
            category = lexit.NUMLIT
        end
    end

    local function handle_EXPONENT()
        if ch == "+" then
            add1()
            state = EXP_AFTER_PLUS
        elseif isDigit(ch) then
            add1()
        else
            state = DONE
            category = lexit.NUMLIT
        end
    end

    local function handle_EXP_AFTER_PLUS()
        if isDigit(ch) then
            add1()
        else
            state = DONE
            category = lexit.NUMLIT
        end

    end


    local function handle_PLUS()
        if isDigit(ch) and not preferOpFlag then
            add1()
            state = DIGIT
        else
            state = DONE
            category = lexit.OP
        end
    end

    local function handle_MINUS()
        if isDigit(ch) and not preferOpFlag then
            add1()
            state = DIGIT
        elseif ch == "-" or ch == "=" then
            state = DONE
            category = lexit.OP
        else
            state = DONE
            category = lexit.OP
        end
    end

    --  = && || ! == != < <= > >= + - * / % [ ] ;
    local function handle_OP()
        if isDoubleOp(lexstr .. ch) then
            add1()
            state = DONE
            category = lexit.OP
        elseif isOp(lexstr) then
            state = DONE
            category = lexit.OP
        else
            state = DONE
            category = lexit.PUNCT
        end
    end

    local function handle_STRLIT()
        add1()

        if ch == '\n' or ch == "" then
            state = DONE
            category = lexit.MAL
        elseif ch == stringQuoteType then
            state = DONE
            category = lexit.STRLIT
        end
    end

    -- ***** Table of State-Handler Functions *****

    handlers = {
        [DONE]=handle_DONE,
        [START]=handle_START,
        [LETTER]=handle_LETTER,
        [DIGIT]=handle_DIGIT,
        [PLUS]=handle_PLUS,
        [MINUS]=handle_MINUS,
        [OP]=handle_OP,
        [EXPONENT]=handle_EXPONENT,
        [EXP_AFTER_PLUS]=handle_EXP_AFTER_PLUS,
        [STRLIT]=handle_STRLIT
    }

    -- ***** Iterator Function *****

    -- getLexeme
    -- Called each time through the for-in loop.
    -- Returns a pair: lexeme-string (string) and category (int), or
    -- nil, nil if no more lexemes.
    local function getLexeme(dummy1, dummy2)
        if pos > program:len() then
            preferOpFlag = false
            return nil, nil
        end
        lexstr = ""
        state = START
        while state ~= DONE do
            ch = currChar()
            handlers[state]()
        end

        skipWhitespace()
        preferOpFlag = false
        return lexstr, category
    end

    -- ***** Body of Function lex *****

    -- Initialize & return the iterator function
    pos = 1
    skipWhitespace()
    return getLexeme, nil, nil
end

return lexit

