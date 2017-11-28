--[[
Game = {}

function Game.Draw(s)
   print("drawing", s)
end

function Game.Texture(a)
   print(a)
   return a
end

function Game.Sprite(tex, x, y, w, h)
   print("new sprite", tex, x, y, w, h)
   return {tex=tex, x=x, y=y, w=w, h=h}
end

function Game.DestroySprite(s)
   print("destroy", s)
end

function Game.DestroyTexture(t)
   print("destroy", t)
end
]]

function makeGlobal(x)
   for k,v in pairs(x) do
      rawset(_G, k, v)
   end
end

makeGlobal(Game)
limit = 10
function Start()
   t = Texture.new("turtle.png")
   s = {}
   for i = 1,limit do
      s[i] = Sprite.new(t, i * 20, i * 50, 128, 128)
      s[i]:draw()
   end
end

x = 0
y = 0

function Update()
   x = x + 10
   y = y + 2   
   for i = 1,limit do
      s[i]:move(x + i * 20, y + i * 80)
      s[i]:draw()
   end
   static.wait(100)
end

function Destroy()
   for i = 1,limit do
      s[i]:destroy()
   end
   Texture.destroy(t)
end

--[[loadScene()
   endScene()]]

