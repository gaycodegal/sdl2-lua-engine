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

function hi(a, b)
   print("yehaw",a,b)
   return getmetatable(a)[b]   
end

function usertostring(x)
   return "userdata"
end

function loadScene()
   t = Game.Texture.new("turtle.png")
   s = {}
   for i = 1,10 do
      s[i] = Game.Sprite.new(t, i * 20, 100 + i * 10, 128, 128)
      s[i].draw()
      --Game.Draw(s[i])
   end
end

function endScene()
   Game.Texture.destroy(t)
end

--[[loadScene()
   endScene()]]

