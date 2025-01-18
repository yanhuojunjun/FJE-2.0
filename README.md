# Funny JSON Explorer

### 1. Project Introduction

Funny JSON Explorer (FJE) is a command-line tool for visualizing JSON files.

```shell
fje -f <json file> -s <style> -i <icon family>
{
    oranges: {
        'mandarin': {                            ├─ oranges
            clementine: null,                    │  └─ mandarin
            tangerine: 'cheap & juicy!'  -=>     │     ├─ clementine
        }                                        │     └─ tangerine: cheap & juicy!
    },                                           └─ apples
    apples: {                                       ├─ gala
        'gala': null,                               └─ pink lady
        'pink lady': null
    }
}
```

FJE allows you to quickly switch styles, including tree (tree) and rectangle (rectangle).

```
├─ oranges                             ┌─ oranges ───────────────────────────────┐
│  └─ mandarin                         │  ├─ mandarin ───────────────────────────┤
│     ├─ clementine                    │  │  ├─ clementine ──────────────────────┤
│     └─ tangerine: cheap & juicy!     │  │  ├─ tangerine: cheap & juicy! ───────┤
└─ apples                              ├─ apples ────────────────────────────────┤
   └─ gala                             └──┴─✩gala ───────────────────────────────┘

        树形（tree）                                   矩形（rectangle）
````

You can also specify an icon family to assign a set of icons to either the middle or leaf nodes.

```
├─♢oranges                                 
│  └─♢mandarin                             
│     ├─♤clementine                        
│     └─♤tangerine: cheap & juicy!    
└─♢apples                                  
   └─♤gala                                 

poker-face-icon-family: Middle node icon: ♢ Leaf node icon: ♤                 
```

### 2. Project Tasks

* FJE-1.0: Using Factory Method, Abstract Factory, Builder, and Composite patterns, complete the functionality while making the program easy to expand and maintain.

1. Without changing the existing code, new styles can be added simply by adding a new abstract factory.

2. New icon families can be added via configuration files.

* FJE-2.0: Refactor the design of the existing FJE-1.0 implementation by adopting the Iterator Pattern and Strategy Pattern.

### 3. Project Operation

Clone the repository:

   ```
   git clone -b master https://github.com/monkek123King/FJE.git
   ```

Create the build folder:

   ```
   cd FJE
   mkdir build
   cd build
   ```

Compile the project:

   ```
   cmake ..
   make    (On Windows, you can use "ninja" in VS Code terminal)
   ```

Change the encoding format (for Windows users in VS Code terminal):

   ```
   chcp 65001
   ```

5. Adjust the input: Project inputs are centralized in the `input` folder. `example.json` is the JSON file to be converted, and `icon.json` is for custom icon families. You can modify these files to adjust the project’s input.

6. Run the program: Input `./fje -help` to get the following output, and then enter the command as needed:

   ```
   Usage: ./fje -f <json file> -s <style> -i <icon family>
   <style>: rectangle or tree
   <icon family>: poker-face or json_defined
   ```

For example, to get the result in rectangle style with a custom icon family, enter the following command:

```
./fje -f ../input/example.json -s rectangle -i json_defined
```

