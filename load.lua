require("tween")
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
limit = 100
function Start()
   t = Texture.new("turtle.png")
   s = {}
   for i = 1,limit do
      local spr = Sprite.new(t, 0, 0, 128, 128)
      local obj = {s=spr, x=(i * 5), y=(i * 50)%300}
      obj.as = {
	 Animation.new({
	       Tween.new(100, (100*i/limit + 10), "x", obj),
	       Tween.new(-100, (100*i/limit + 10), "x", obj)
	 }),
	 Animation.new({
	       Tween.new(100, 100, "y", obj),
	       Tween.new(-100, 100, "y", obj)
	    })
      }
      obj.s:draw()
      s[i] = obj
   end
end

x = 0
y = 0
dx = 10
dy = 2
times = 50
function Update()
   --[[x = x + dx
   y = y + dy
   times = times - 1
   if times == 0 then
      dx = -dx
      dy = -dy
      times = 50
      end]]
   for i, spr in ipairs(s) do
      for k, v in ipairs(spr.as) do
	 v:step(5)
      end
      spr.s:move(spr.x,spr.y)
      spr.s:draw()
   end
   static.wait(math.floor(1000/60))
end

--Update = nil

function Destroy()
   for i = 1,limit do
      s[i]:destroy()
   end
   Texture.destroy(t)
end

--[[loadScene()
   endScene()]]

