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

function loadScene()
   t = Game.Texture.new("turtle.png")
   s = {}
   for i = 1,10 do
      s[i] = Game.Sprite.new(t, i * 20, 100 + i * 10, 128, 128)
      print(getmetatable(s[i]))
      for k, v in pairs(getmetatable(s[i])) do
	 print(k, v)
      end
      print(s[i])
      print(getmetatable(s[i])["draw"](s[i]))
      print("?")
      s[i].draw()
      --Game.Draw(s[i])
   end
end

function endScene()
   t.destroy()
end

--[[loadScene()
   endScene()]]
