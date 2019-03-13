const int cMazeColumns = 21;
const int cMazeRows = 21;

const char cEmptySymbol = ' ';
const char cWallSymbol = 'X';
const char cCharacterSymbol = '@';
const char cExitSymbol = '#';
const char cKeySymbol = 'K';

using Maze = std::array<std::array<char, cMazeColumns>, cMazeRows>;

bool scanForCharS(const Maze &maze,
                 const char charToFind,
                 int prCharRow,
                 int prCharColumn);
