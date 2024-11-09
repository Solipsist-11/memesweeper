#include "MemeField.h"
#include <random>

MemeField::Tile::Tile(Vei2 in_pos)
	:
	gridPos(in_pos)
{
}

Vei2 MemeField::Tile::GetGPos() const
{
	return gridPos;
}

bool MemeField::Tile::HasMeme() const
{
	return hasMeme;
}

void MemeField::Tile::Draw(Graphics& gfx) const
{
		switch (stat)
		{
		case State::Hidden:
			SpriteCodex::DrawTileButton(gridPos.GridtoScreenPos(), gfx);
			break;
		case State::Flagged:
			SpriteCodex::DrawTileFlag(gridPos.GridtoScreenPos(), gfx);
			break;
		case State::Revealed:
			if (hasMeme)
			{
				SpriteCodex::DrawTileBomb(gridPos.GridtoScreenPos(), gfx);
				break;
			}
			else
			{
				SpriteCodex::DrawTile0(gridPos.GridtoScreenPos(), gfx);
				break;
			}
		}
}

void MemeField::Tile::RevealTile()
{
	if (stat == State::Hidden)
	{
		stat = State::Revealed;
	}
}

void MemeField::Tile::FlagTile()
{
	if (stat == State::Hidden)
	{
		stat = State::Flagged;
	}
}

void MemeField::Tile::SetMeme()
{
	hasMeme = true;
}

MemeField::MemeField(int in_Memes)
	:
	nMemes(in_Memes)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int>xDist(0, width - 1);
	std::uniform_int_distribution<int>yDist(0, height - 1);

	for (int i = 0; i < width * height; i++)
	{
		tilefield[i] = Tile(Vei2(i / width, i % width));
	}
	for (int n = 0; n < nMemes; n++)
	{
		Vei2 newPos = { xDist(rng), yDist(rng) };
		do
		{
			TileAt(newPos).SetMeme();
		} while (!tilefield[newPos.y * width + newPos.x].HasMeme());
	}
}

void MemeField::Draw(Graphics& gfx) const
{
	gfx.DrawRect(0, 0, width * SpriteCodex::tileSize - 1, height * SpriteCodex::tileSize - 1, SpriteCodex::baseColor);

	for (Tile t : tilefield)
	{
		t.Draw(gfx);
	}
}

MemeField::Tile& MemeField::TileAt(Vei2 gridP)
{
	return tilefield[gridP.y * width + gridP.x];
}

const MemeField::Tile& MemeField::TileAt(Vei2 gridP) const
{
	return tilefield[gridP.y * width + gridP.x];
}
