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
   t = Game.Texture("turtle.png")
   s = {}
   for i = 1,10 do
      s[i] = Game.Sprite(t, i * 20, 100 + i * 10, 128, 128)
      Game.Draw(s[i])
   end
end

function endScene()
   for i, sprite in pairs(s) do
      Game.DestroySprite(sprite)
   end
   Game.DestroyTexture(t)
end

--[[loadScene()
   endScene()]]
