-- pa2.lua
-- William Horn
-- HW 2, Exersice B

local pa2 = {}

-- filterArray, concatMax, collatz.

function pa2.mapArray(func, arr)
    local mapped = {}

    for i, val in ipairs(arr) do
        mapped[i] = func(val)
    end

    return mapped
end

function pa2.concatMax(str, num)
    local total = ""

    for _ = 0, num do
        if string.len(total) + string.len(str) > num then
            return total
        end

        total = total .. str
    end

    return total
end

local function multBy2(x)
    return x * 2
end


function pa2.collatz(n)
    while true do
        coroutine.yield(n)
        if n == 1 then
            return
        elseif n % 2 == 1 then
            n = 3 * n + 1
        else
            n = n / 2
        end

    end
end



return pa2
