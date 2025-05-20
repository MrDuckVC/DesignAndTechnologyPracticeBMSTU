#include "Tile.hpp"

Texture Tile::flagTexture;
Texture Tile::mineTexture;

void Tile::LoadTexture() {
	Tile::flagTexture.loadFromFile(FLAG);
	Tile::mineTexture.loadFromFile(BOMB);
}

Tile::Tile() : number(font), flagSprite(flagTexture), mineSprite(mineTexture)
{
	outline = Color(100, 100, 100, 255);
	default_Color = Color(150, 150, 150, 255);
	reveal = Color(50, 50, 50, 255);
	blasted = Color(200, 0, 0, 255);
	marked = Color(0, 200, 0, 255);

	adjacentCount = 0;
	isBomb = false;
	isBlasted = false;
	isRevealed = false;
	isMarked = false;

	number.setString("");

	flagSprite.setScale({0.14f, 0.14f});
	mineSprite.setScale({0.04f, 0.04f});
}

void Tile::CreateTile(Vector2f pos, Vector2f size)
{
	tile.setPosition(pos);
	tile.setSize(size);
	tile.setFillColor(default_Color);
	tile.setOutlineColor(outline);
	tile.setOutlineThickness(3.f);
}

void Tile::SetAdjacent(int count)
{
	adjacentCount = count;
	std::stringstream ss;
	ss << adjacentCount;
	number.setString(ss.str());


	if (!font.openFromFile("assests/Fonts/static/Orbitron-Black.ttf")) {
        throw std::runtime_error("Failed to load minesweeper font");
    }

	number.setFont(font);
	number.setFillColor(Color::White);
	number.setPosition(Vector2f(
		tile.getPosition().x + tile.getSize().x / 3,
		tile.getPosition().y + 5));
}

void Tile::SetBomb()
{
	isBomb = true;
	// mineTexture.loadFromFile(BOMB);
	mineSprite.setTexture(mineTexture);
	mineSprite.setPosition(tile.getPosition() + Vector2f(10.f, 10.f));
}

bool Tile::IsBomb()
{
	return isBomb;
}

int Tile::Mark()
{
	if (isRevealed)
		return -1;

	isMarked = !isMarked;
	if (isMarked) {
		tile.setFillColor(marked);
		// flagTexture.loadFromFile(FLAG);
		flagSprite.setTexture(flagTexture);
		flagSprite.setPosition(tile.getPosition() + Vector2f(15.f, 10.f));
	}
	else {
		tile.setFillColor(default_Color);
	}

	return isMarked;
}

bool Tile::IsRevealed()
{
	return isRevealed;
}

bool Tile::Reveal(bool clicked)
{
	if (isRevealed || isMarked)
		return false;

	isRevealed = true;
	tile.setFillColor(reveal);

	if (isBomb && clicked)
	{
		isBlasted = true;
		tile.setFillColor(blasted);
	}

	return true;
}

int Tile::GetAdjacentCount()
{
	return adjacentCount;
}

void Tile::Render(RenderWindow& window)
{
	window.draw(tile);
	if (isRevealed)
	{
		if (isBomb)
		{
			window.draw(mineSprite);
		}
		else if (adjacentCount > 0)
		{
			window.draw(number);
		}
	}
	if (isMarked)
	{
		window.draw(flagSprite);
	}
}
