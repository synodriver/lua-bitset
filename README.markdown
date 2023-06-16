# lua-bitset

### lua binding for [bitset](https://github.com/lemire/cbitset)

### usage

```lua
local bitset = require("bitset")

local b = bitset.new()

for k = 0, 999 do
    b:set(3 * k)
end

assert(b:count()==1000)
assert(b:get(3)==true)

for v in b:iter() do
    print(v)
end

b:for_each(function(v)
    print("this is ".. v)
    --error("nooo!")
    return true
end

)
```