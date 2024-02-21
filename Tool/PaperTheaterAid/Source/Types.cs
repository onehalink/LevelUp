enum Element
{
    Empty,
    Box,
    Car,
    Grass,
    Food,
    Mountain,
    Tree,

    LockA,
    KeyA,

    LockB,
    KeyB,

    LockC,
    KeyC,

    Actor,
    Footprint,

    Count,
};


enum ConsoleColor
{
    Red,
    Green,
    Blue,
    Yellow,
    Cyan,
    Magenta,
    White,
    Black,
}


struct Vector2Int
{
    public int x;
    public int y;


    public Vector2Int(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
}


class Level
{
    public struct ActorRecord
    {
        public string name;
        public Vector2Int origin;
        public int moveLimit;


        public ActorRecord(string name, Vector2Int origin, int moveLimit)
        {
            this.name = name;
            this.origin = origin;
            this.moveLimit = moveLimit;
        }
    }


    public struct EntityRecord
    {
        public Element element;
        public Vector2Int position;


        public EntityRecord(Element element, Vector2Int position)
        {
            this.element = element;
            this.position = position;
        }
    }


    public List<ActorRecord> actorRecords;
    public List<EntityRecord> entityRecords;


    public Level()
    {
        actorRecords = new List<ActorRecord>();
        entityRecords = new List<EntityRecord>();
    }
}