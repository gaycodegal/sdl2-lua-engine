function woof()
   print("woof")
end


function upset(x, y)
   print(x,y)
end
function indexer(x,y)
   print(x,y)
   return a[y]
end

a = {__index = indexer, dog=woof}
b = {}
setmetatable(b, a)
b.dog()


function add(x, y)
   return 33
end

print(b.c)
a.__add = add
print(b+b)
