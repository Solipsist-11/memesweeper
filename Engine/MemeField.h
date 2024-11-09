#pragma once
#include "Vei2.h"
#include "RectI.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Colors.h"

class MemeField
{
private:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Revealed,
			Flagged
		};
	public:
		Tile() = default;
		Tile(Vei2 in_pos);
		Vei2 GetGPos() const;
		bool HasMeme() const;
		void Draw(Graphics& gfx) const;
		void RevealTile();
		void FlagTile();
		void SetMeme();
	private:
		Vei2 gridPos;
		State stat = State::Hidden;
		bool hasMeme = false;
	};
public:
	MemeField(int in_Memes);
	void Draw(Graphics& gfx) const;
	Tile& TileAt(Vei2 gridP);
	const Tile& TileAt(Vei2 gridP) const;
private:
	static constexpr int width = 20;
	static constexpr int height = 20;
	Tile tilefield[width * height];
	int nMemes = 0;
	
};

