/*
Block Programmed by James Whyatt, last updated 4/27/20
Tests collision between two rectangle shapes, with shape1 moving dist in direction dir. 'W' Up 'A' Left 'S' down 'D' right. dir can be lowercase.
Returns true if the two rectangles intersect in the given movement.
*/
bool testCollision(sf::RectangleShape shape1, sf::RectangleShape shape2, char dir, int dist)
{
	dir = toupper(dir);

	sf::Vector2f pos1 = shape1.getPosition();
	if (dir == 'W')
		pos1.y -= dist;
	if (dir == 'A')
		pos1.x -= dist;
	if (dir == 'S')
		pos1.y += dist;
	if (dir == 'D')
		pos1.x += dist;
	sf::Vector2f dimension1 = shape1.getSize();
	sf::Vector2f pos2 = shape2.getPosition();
	sf::Vector2f dimension2 = shape2.getSize();

	bool checkX = false, checkY = false; 
	//checkX is checked true if one shape or the other is within X bounds, and vice versa for checkY

	//check if shape2 is within bounds of shape1
	//X 1
	if ((pos2.x >= pos1.x) && (pos2.x < (pos1.x + dimension1.x)))
		checkX = true; //the origin of object 2 is within X bounds of object 1.

	//Y 1
	if ((pos2.y >= pos1.y) && (pos2.y < (pos1.y + dimension1.y)))
		checkY = true; //the origin of object 2 is within Y bounds of object 1.

	//check if shape1 is within bounds of shape2
	//X2
	if ((pos1.x >= pos2.x) && (pos1.x < (pos2.x + dimension2.x)))
		checkX = true; //the origin of object 1 is within X bounds of object 2.

	//Y2
	if ((pos1.y >= pos2.y) && pos1.y < (pos2.y + dimension2.y))
		checkY = true; //the origin of object 1 is within Y bounds of object 2.

	if (checkX == true && checkY == true)
		return true;
	else
		return false;
}