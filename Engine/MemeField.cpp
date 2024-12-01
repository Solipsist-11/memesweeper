#include "MemeField.h"
#include <random>
#include <cmath>
#include <assert.h>

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
			switch (adjacentMemes)
			{
			case 0:
				SpriteCodex::DrawTile0(gridPos.GridtoScreenPos(), gfx);
				break;
			case 1:
				SpriteCodex::DrawTile1(gridPos.GridtoScreenPos(), gfx);
				break;
			case 2:
				SpriteCodex::DrawTile2(gridPos.GridtoScreenPos(), gfx);
				break;
			case 3:
				SpriteCodex::DrawTile3(gridPos.GridtoScreenPos(), gfx);
				break;
			case 4:
				SpriteCodex::DrawTile4(gridPos.GridtoScreenPos(), gfx);
				break;
			case 5:
				SpriteCodex::DrawTile5(gridPos.GridtoScreenPos(), gfx);
				break;
			case 6:
				SpriteCodex::DrawTile6(gridPos.GridtoScreenPos(), gfx);
				break;
			case 7:
				SpriteCodex::DrawTile7(gridPos.GridtoScreenPos(), gfx);
				break;
			case 8:
				SpriteCodex::DrawTile8(gridPos.GridtoScreenPos(), gfx);
				break;
			}
		}
	}
}

void MemeField::Tile::RevealTile()
{
	if (stat == State::Hidden && stat != State::Flagged)
	{
		stat = State::Revealed;
	}
}

void MemeField::Tile::FlagTile()
{
	if (stat == State::Hidden && stat != State::Revealed)
	{
		stat = State::Flagged;
	}
}

void MemeField::Tile::SetMeme()
{
	hasMeme = true;
}

void MemeField::Tile::SetAdjMemes(int in_adj)
{
	adjacentMemes = in_adj;
}

bool MemeField::Tile::CheckFlag()
{
	return(stat == State::Flagged);
}

bool MemeField::Tile::HasRevealedMeme()
{
	
	return (hasMeme == true && stat == State::Revealed);
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
		tilefield[i] = Tile(Vei2(i % width, i / width));
	}
	for (int n = 0; n < nMemes; n++)
	{
		Vei2 newPos = { xDist(rng), yDist(rng) };
		do
		{
			TileAt(newPos).SetMeme();
			memearray[n] = newPos.y * width + newPos.x;
		} while (!tilefield[newPos.y * width + newPos.x].HasMeme());
	}
}

void MemeField::Draw(Graphics& gfx) const
{
	gfx.DrawRect(250, 120, width * SpriteCodex::tileSize +250 - 1, height * SpriteCodex::tileSize +120 - 1, SpriteCodex::baseColor);

	for (const Tile& t : tilefield)
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

void MemeField::UpdateMemeAdjCounter()
{
	for (int i = 0; i < (width * height); i++)
	{
		int x = i % width;
		int y = i / width;

		int x_min = std::max(x - 1, 0);
		int y_min = std::max(y - 1, 0);
		int x_max = std::min(x + 1, width - 1);
		int y_max = std::min(y + 1, height - 1);

		assert(x_min >= 0 && x_max <= width - 1);
		assert(y_min >= 0 && y_max <= height - 1);

		int memeCounter = 0;

		for (int xn = x_min; xn <= x_max; xn++)
		{
			for (int yn = y_min; yn <= y_max; yn++)
			{
				if ( TileAt(Vei2(xn, yn)).HasMeme() )
				{
					memeCounter++;
				}
			}
		}
		assert(memeCounter >= 0 && memeCounter <= 8);

		tilefield[i].SetAdjMemes(memeCounter);
	}
}

bool MemeField::GameOverCheck()
{
	bool GameOver = false;
	for (int n = 0; n < nMemes; n++)
	{
		GameOver = GameOver || tilefield[memearray[n]].HasRevealedMeme();
	}
	return GameOver;
}

bool MemeField::WinCheck()
{
	bool game_win = true;
	for (int n = 0; n < nMemes; n++)
	{
		game_win = game_win && tilefield[memearray[n]].CheckFlag();
	}
	return game_win;
}
