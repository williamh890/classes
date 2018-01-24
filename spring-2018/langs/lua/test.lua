-- William Test File
-- This is a comment

-- Hello World!
print("Hello\n")

nicePrint = function(header, f)
    print(header)
    f()
    print('')
end

-- Regular Arithmatic
arithmatic = function()
    x = 2 + 2
    x = x * 9
    x = x^7
    x = 42E19
    print(x)
end

concat = function()
    first = "William "
    last = "Horn"
    print( first .. last )
end

bools = function()
    t, f = true, f
    print(not t)
    print(t and f)
    print(t or f)

    -- jank terinary
    h, b = 'hello', 'bye'
    v = t and b or h
end

-- Equality and Inequality
eq_ineq = function()
    print("Equality/Inequality")
    print(1 == 0)
    print(1 ~= 0)
end

tables = function()
    table = {["hello"] = 12, [function() end]="What?!", noBrace = 13, 12}
    print(table)
    print("length: " .. #table)
    nums = {1, 2, 3, 4}
    -- Two different appends
    table.insert(nums, 5)
    -- Insert at index 1
    table.insert(nums, 1, 0)
    nums[#nums + 1] = 6
    table.remove(nums, 1)
    print(nums)

    t = {"w", "a", "m"}
    table.concat(t, '-')
    print(t)
end

reflectiveness = function()
    b = true
    print(b, type(b))
    b = "HELLO"
    print(b, type(b))
    b = 7
    print(b, type(b))
    b = function() print("YO") end
    print(b, type(b))
end

multi = function()
    a, b, c = 1 + 13, "BOB", true
    print(a, b, c)
end

s2n = function()
    n = tonumber("1234")
    print(n)
end

coersion = function()
    x = 14
    print(n + "14")
    print(x == "14")
end

strings = function()
    s1, s2, s3 = "hello", 'hello', [[hello]]
    noEscape = [[\n\n\n\n\n]]
    print(noEscape)
    concat = s1 .. 14
    print(concat)
    sf = string.format('%.3f', 5.2)
    print(sf)
end

control = function()
    word = 'bye'
    if word == hello then
        print('1')
    elseif word == sup then
        print('2')
    else
        print('3')
    end
    x = -1
    while x < 1 do
        print('looping!')
        x = x + 1
    end

    repeat
        print('repeating!')
        x = x - 1
    until x == -1

    for i = 0, 10, 2 do
        print(i)
    end

    --  has a break statement, no continue tho.

end



demoFuncs = {
    {"Arithmatic", arithmatic},
    {"Strings", concat},
    {"Booleans", bools},
    {"Equality/Inquality", eq_ineq},
    {"Tables", tables},
    {"Type Checking", reflectiveness},
    {"Multi Assignment", multi},
    {"String to number", s2n},
    {"Coersion", coersion},
    {"Strings", strings}
}

for k, v in ipairs(demoFuncs) do
    label = v[1]
    func = v[2]
    nicePrint(label, func)
end
