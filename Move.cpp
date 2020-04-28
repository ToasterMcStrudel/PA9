/*
Programmed by James Whyatt, last updated 4/27/20
Modifies the passed vector by deltX and deltY, and returns the new coordinates.
Can also be used to resize a rectangle of size sf::Vector2f, if need be.
*/
sf::Vector2f move(int deltX, int deltY, sf::Vector2f startcoords)
{
	if((startcoords.x + deltX) >= 0 && (startcoords.x + deltX) < WINDOWLENGTH)
		startcoords.x += deltX;
	if((startcoords.y + deltY) >= 0 && (startcoords.y + deltY) < WINDOWHEIGHT)
		startcoords.y += deltY;

	return startcoords;
}