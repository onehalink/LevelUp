using System.IO;
using System.Text;


const string LineFeed = "\n";


var StringToElementHelper = (string data) =>
{
    foreach (var element in data.Split(','))
    {
        var name = element.Trim();
        var length = name.Length;

        Console.WriteLine($"if(count == {length} && Memory::Equal(text, \"{name}\", {length})) return Element::{name};");
    }
};

var StringToColorHelper = (string data) =>
{
    foreach (var element in data.Split(','))
    {
        var name = element.Trim();
        var length = name.Length;

        Console.WriteLine($"if(count == {length} && Memory::Equal(text, \"{name}\", {length})) return {name};");
    }
};

var BuildActorDescriptorAsset = (string path, string name, string footprint, ConsoleColor foreground, ConsoleColor background) =>
{
    var sb = new StringBuilder();

    sb.Append(name).Append(LineFeed);
    sb.Append(footprint).Append(LineFeed);
    sb.Append(foreground.ToString()).Append(LineFeed);
    sb.Append(background.ToString()).Append(LineFeed);

    File.WriteAllText(path, sb.ToString());
};

var BuildElementDescriptorAsset = (string path, string name, ConsoleColor foreground, ConsoleColor background) =>
{
    var sb = new StringBuilder();

    sb.Append(name).Append(LineFeed);
    sb.Append(foreground.ToString()).Append(LineFeed);
    sb.Append(background.ToString()).Append(LineFeed);

    File.WriteAllText(path, sb.ToString());
};

var BuildDescriptionAsset = (string path, string level, string move, string whenClear) =>
{
    var sb = new StringBuilder();

    sb.Append(level).Append(LineFeed);
    sb.Append(move).Append(LineFeed);
    sb.Append(whenClear).Append(LineFeed);

    File.WriteAllText(path, sb.ToString());
};

var BuildLevelAsset = (string path, Level level) =>
{
    //const string LineFeed = "\n";

    var sb = new StringBuilder();

    sb.Append("[Actor]").Append(LineFeed);
    sb.Append($"Count={level.actorRecords.Count}").Append(LineFeed);
    foreach (var record in level.actorRecords)
        sb.Append($"{record.name}, {record.origin.x}, {record.origin.y}, {record.moveLimit}").Append(LineFeed);

    sb.Append(LineFeed);

    sb.Append("[Entity]").Append(LineFeed);
    sb.Append($"Count={level.entityRecords.Count}").Append(LineFeed);
    foreach (var record in level.entityRecords)
        sb.Append($"{record.element.ToString()}, {record.position.x}, {record.position.y}").Append(LineFeed);

    File.WriteAllText(path, sb.ToString());
};


if(false)
{
    for(int i = 0; i < (int)Element.Count; i++)
    {
        Console.WriteLine($"\"Asset/Element/{((Element)i).ToString()}.txt\",");
    }

    for (int i = 1; i < 10; i++)
    {
        Console.WriteLine($"\"Asset/Level {i}.txt\",");
    }

    return;
}

if(false)
{
    StringToElementHelper("    Box,\r\n\tCar,\r\n\tGrass,\r\n\tFood,\r\n\tMountain,\r\n\tTree,\r\n\r\n    LockA,\r\n    KeyA,\r\n\r\n    LockB,\r\n    KeyB,\r\n\r\n    LockC,\r\n    KeyC,\r\n\r\n    Actor,\r\n\tFootprint,");
    return;
}

if (false)
{
    StringToColorHelper("    Red,\r\n    Green,\r\n    Blue,\r\n    Yellow,\r\n    Cyan,\r\n    Magenta,\r\n    White,\r\n    Black,");
    return;
}


var outputDirectory = "Asset";
if (!Directory.Exists(outputDirectory)) Directory.CreateDirectory(outputDirectory);

var actorDescriptorDirectory = Path.Combine(outputDirectory, "Actor");
if (!Directory.Exists(actorDescriptorDirectory)) Directory.CreateDirectory(actorDescriptorDirectory);

var elementDescriptorDirectory = Path.Combine(outputDirectory, "Element");
if (!Directory.Exists(elementDescriptorDirectory)) Directory.CreateDirectory(elementDescriptorDirectory);

// ActorDescriptor
{
    // GuoBa
    {
        var path = Path.Combine(actorDescriptorDirectory, "GuoBa.txt");
        BuildActorDescriptorAsset(path, "锅", "++", ConsoleColor.Yellow, ConsoleColor.Black);
    }

    // YueGui
    {
        var path = Path.Combine(actorDescriptorDirectory, "YueGui.txt");
        BuildActorDescriptorAsset(path, "月", "++", ConsoleColor.Green, ConsoleColor.Black);
    }
}

// ElementDescriptor
{
    // Empty
    {
        var path = Path.Combine(elementDescriptorDirectory, "Empty.txt");
        BuildElementDescriptorAsset(path, "口", ConsoleColor.White, ConsoleColor.Black);
    }

    // Box
    {
        var path = Path.Combine(elementDescriptorDirectory, "Box.txt");
        BuildElementDescriptorAsset(path, "箱" , ConsoleColor.White, ConsoleColor.Black);
    }

    // Car
    {
        var path = Path.Combine(elementDescriptorDirectory, "Car.txt");
        BuildElementDescriptorAsset(path, "车", ConsoleColor.White, ConsoleColor.Black);
    }

    // Grass
    {
        var path = Path.Combine(elementDescriptorDirectory, "Grass.txt");
        BuildElementDescriptorAsset(path, "草", ConsoleColor.White, ConsoleColor.Black);
    }

    // Food
    {
        var path = Path.Combine(elementDescriptorDirectory, "Food.txt");
        BuildElementDescriptorAsset(path, "食", ConsoleColor.White, ConsoleColor.Black);
    }

    // Mountain
    {
        var path = Path.Combine(elementDescriptorDirectory, "Mountain.txt");
        BuildElementDescriptorAsset(path, "山", ConsoleColor.White, ConsoleColor.Black);
    }

    // Tree
    {
        var path = Path.Combine(elementDescriptorDirectory, "Tree.txt");
        BuildElementDescriptorAsset(path, "树", ConsoleColor.White, ConsoleColor.Black);
    }

    // LockA
    {
        var path = Path.Combine(elementDescriptorDirectory, "LockA.txt");
        BuildElementDescriptorAsset(path, "锁", ConsoleColor.Red, ConsoleColor.Black);
    }

    // LockB
    {
        var path = Path.Combine(elementDescriptorDirectory, "LockB.txt");
        BuildElementDescriptorAsset(path, "锁", ConsoleColor.Green, ConsoleColor.Black);
    }

    // LockC
    {
        var path = Path.Combine(elementDescriptorDirectory, "LockC.txt");
        BuildElementDescriptorAsset(path, "锁", ConsoleColor.Blue, ConsoleColor.Black);
    }

    // KeyA
    {
        var path = Path.Combine(elementDescriptorDirectory, "KeyA.txt");
        BuildElementDescriptorAsset(path, "钥", ConsoleColor.Red, ConsoleColor.Black);
    }

    // KeyB
    {
        var path = Path.Combine(elementDescriptorDirectory, "KeyB.txt");
        BuildElementDescriptorAsset(path, "钥", ConsoleColor.Green, ConsoleColor.Black);
    }

    // KeyC
    {
        var path = Path.Combine(elementDescriptorDirectory, "KeyC.txt");
        BuildElementDescriptorAsset(path, "钥", ConsoleColor.Blue, ConsoleColor.Black);
    }

    // Actor
    {
        var path = Path.Combine(elementDescriptorDirectory, "Actor.txt");
        BuildElementDescriptorAsset(path, "玩", ConsoleColor.Yellow, ConsoleColor.Black);
    }

    // Footprint
    {
        var path = Path.Combine(elementDescriptorDirectory, "Footprint.txt");
        BuildElementDescriptorAsset(path, "++", ConsoleColor.Yellow, ConsoleColor.Black);
    }
}

{
    var path = Path.Combine(outputDirectory, "Description.txt");
    BuildDescriptionAsset(path, "关卡", "行动值：", "提示：判定关卡通过");
}


// Level 1
{
    var level = new Level();

    level.actorRecords.Add(new Level.ActorRecord("锅巴", new Vector2Int(3, 5), 8));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(6, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(7, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(8, 1)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(4, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(5, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Food, new Vector2Int(7, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(8, 2)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(6, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(7, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(8, 3)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(2, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(3, 5)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(2, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(3, 6)));

    var path = Path.Combine(outputDirectory, "Level 1.txt");
    BuildLevelAsset(path, level);
}

// Level 2
{
    var level = new Level();

    level.actorRecords.Add(new Level.ActorRecord("月桂", new Vector2Int(4, 5), 5));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(3, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Food, new Vector2Int(4, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(5, 0)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(3, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockC, new Vector2Int(4, 1)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(5, 2)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(7, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyC, new Vector2Int(8, 3)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(7, 4)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(3, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(4, 5)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(4, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(5, 6)));

    var path = Path.Combine(outputDirectory, "Level 2.txt");
    BuildLevelAsset(path, level);
}

// Level 3
{
    var level = new Level();

    level.actorRecords.Add(new Level.ActorRecord("锅巴", new Vector2Int(4, 4), 6));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(5, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Food, new Vector2Int(6, 0)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(5, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockC, new Vector2Int(6, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(7, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(8, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(9, 1)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(1, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(2, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(5, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyC, new Vector2Int(9, 2)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(1, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(4, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(9, 3)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(4, 4)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(4, 5)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(0, 7)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(1, 7)));

    var path = Path.Combine(outputDirectory, "Level 3.txt");
    BuildLevelAsset(path, level);
}

// Level 4
{
    var level = new Level();

    level.actorRecords.Add(new Level.ActorRecord("锅巴", new Vector2Int(2, 4), 6));
    level.actorRecords.Add(new Level.ActorRecord("月桂", new Vector2Int(2, 5), 7));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(7, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(8, 2)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(2, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Food, new Vector2Int(7, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(8, 3)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(1, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(2, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(6, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockC, new Vector2Int(7, 4)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(1, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(2, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(3, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(4, 5)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(2, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyC, new Vector2Int(7, 6)));

    var path = Path.Combine(outputDirectory, "Level 4.txt");
    BuildLevelAsset(path, level);
}

// Level 5
{
    var level = new Level();

    level.actorRecords.Add(new Level.ActorRecord("锅巴", new Vector2Int(1, 4), 7));
    level.actorRecords.Add(new Level.ActorRecord("月桂", new Vector2Int(9, 4), 6));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(0, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyA, new Vector2Int(5, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(8, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(9, 0)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(1, 1)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(3, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(6, 2)));

    level.entityRecords.Add(new Level.EntityRecord(Element.LockC, new Vector2Int(3, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Food, new Vector2Int(6, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(7, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(8, 3)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(0, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(1, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(4, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(5, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockB, new Vector2Int(6, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockA, new Vector2Int(7, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(9, 4)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(1, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(3, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyC, new Vector2Int(7, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(8, 5)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(1, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(2, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(3, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(4, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(5, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(8, 6)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(4, 7)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyB, new Vector2Int(5, 7)));

    var path = Path.Combine(outputDirectory, "Level 5.txt");
    BuildLevelAsset(path, level);
}

// Level 6
{
    var level = new Level();

    level.actorRecords.Add(new Level.ActorRecord("锅巴", new Vector2Int(1, 5), 7));
    level.actorRecords.Add(new Level.ActorRecord("月桂", new Vector2Int(5, 6), 6));

    level.entityRecords.Add(new Level.EntityRecord(Element.KeyC, new Vector2Int(0, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(3, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(5, 0)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(3, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Food, new Vector2Int(4, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockA, new Vector2Int(5, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(6, 1)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(0, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(6, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyA, new Vector2Int(8, 2)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(5, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(9, 3)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(1, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(4, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(5, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(6, 4)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(0, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(1, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(4, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockC, new Vector2Int(6, 5)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(1, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(4, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(5, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(6, 6)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(2, 7)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(3, 7)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(5, 7)));

    var path = Path.Combine(outputDirectory, "Level 6.txt");
    BuildLevelAsset(path, level);
}

// Level 7
{
    var level = new Level();

    level.actorRecords.Add(new Level.ActorRecord("锅巴", new Vector2Int(4, 4), 5));
    level.actorRecords.Add(new Level.ActorRecord("月桂", new Vector2Int(6, 4), 5));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(9, 0)));

    level.entityRecords.Add(new Level.EntityRecord(Element.KeyC, new Vector2Int(1, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(5, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyA, new Vector2Int(9, 1)));

    level.entityRecords.Add(new Level.EntityRecord(Element.LockC, new Vector2Int(4, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Food, new Vector2Int(5, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockA, new Vector2Int(6, 2)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(0, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(4, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(5, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(6, 3)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(2, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(4, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(6, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(8, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(9, 4)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(4, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(5, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(6, 5)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(0, 7)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(1, 7)));

    var path = Path.Combine(outputDirectory, "Level 7.txt");
    BuildLevelAsset(path, level);
}

// Level 8
{
    var level = new Level();

    level.actorRecords.Add(new Level.ActorRecord("锅巴", new Vector2Int(6, 4), 4));
    level.actorRecords.Add(new Level.ActorRecord("月桂", new Vector2Int(5, 3), 5));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(4, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(5, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(7, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(9, 0)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Food, new Vector2Int(4, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockA, new Vector2Int(5, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(8, 1)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(1, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(5, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(7, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(8, 2)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(1, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(2, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(3, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(5, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(9, 3)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(5, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(6, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(9, 4)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(0, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockC, new Vector2Int(5, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(7, 5)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(6, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(7, 6)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(3, 7)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyA, new Vector2Int(5, 7)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyC, new Vector2Int(8, 7)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(9, 7)));

    var path = Path.Combine(outputDirectory, "Level 8.txt");
    BuildLevelAsset(path, level);
}

// Level 9
{
    var level = new Level();

    level.actorRecords.Add(new Level.ActorRecord("锅巴", new Vector2Int(4, 5), 5));
    level.actorRecords.Add(new Level.ActorRecord("月桂", new Vector2Int(4, 3), 4));

    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(2, 0)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(4, 0)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(1, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyC, new Vector2Int(5, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(6, 1)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(9, 1)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(4, 2)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyB, new Vector2Int(9, 2)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(4, 3)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Tree, new Vector2Int(9, 3)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(4, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(5, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Box, new Vector2Int(6, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(7, 4)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockB, new Vector2Int(8, 4)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Car, new Vector2Int(4, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockC, new Vector2Int(5, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.LockA, new Vector2Int(7, 5)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Food, new Vector2Int(8, 5)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(0, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(3, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(4, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(6, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(7, 6)));
    level.entityRecords.Add(new Level.EntityRecord(Element.Grass, new Vector2Int(8, 6)));

    level.entityRecords.Add(new Level.EntityRecord(Element.Mountain, new Vector2Int(4, 7)));
    level.entityRecords.Add(new Level.EntityRecord(Element.KeyA, new Vector2Int(8, 7)));

    var path = Path.Combine(outputDirectory, "Level 9.txt");
    BuildLevelAsset(path, level);
}