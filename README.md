# Funny JSON Explorer

### 一. 项目介绍

Funny JSON Explorer（**FJE**），是一个JSON文件可视化的命令行界面小工具

```shell
fje -f <json file> -s <style> -i <icon family>
```


```
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
````

FJE可以快速切换**风格**（style），包括：树形（tree）、矩形（rectangle）；

```
├─ oranges                             ┌─ oranges ───────────────────────────────┐
│  └─ mandarin                         │  ├─ mandarin ───────────────────────────┤
│     ├─ clementine                    │  │  ├─ clementine ──────────────────────┤
│     └─ tangerine: cheap & juicy!     │  │  ├─ tangerine: cheap & juicy! ───────┤
└─ apples                              ├─ apples ────────────────────────────────┤
   └─ gala                             └──┴─✩gala ───────────────────────────────┘

        树形（tree）                                   矩形（rectangle）
````

也可以指定**图标族**（icon family），为中间节点或叶节点指定一套icon

```
├─♢oranges                                 
│  └─♢mandarin                             
│     ├─♤clementine                        
│     └─♤tangerine: cheap & juicy!    
└─♢apples                                  
   └─♤gala                                 

poker-face-icon-family: 中间节点icon：♢ 叶节点icon：♤                 
```

### 二. 项目任务

使用**工厂方法**（Factory）、**抽象工厂**（Abstract Factory）、**建造者**（Builder）模式、**组合模式**（Composition），完成功能的同时，使得程序易于扩展和维护。

1. 不改变现有代码，只需添加新的抽象工厂，即可添加新的风格
2. 通过配置文件，可添加新的图标族

### 三. 项目运行方式

1. 克隆仓库

   ```
   git clone -b master https://github.com/monkek123King/FJE.git
   ```

2. 创建build文件夹

   ```
   cd FJE
   mkdir build
   cd build
   ```

3. 编译项目

   ```
   cmake ..
   make    (windows vscode终端可以使用“ninja”)
   ```

4. 转换编码方式 (windows vscode终端下)

   ```
   chcp 65001
   ```

5. 调整输入：项目输入集中在`input`文件夹下，`example.json` 为待转换的json文件，`icon.json`为自定义的图标族，可以改动这些文件来调整项目的输入

6. 执行程序：输入`./fje -help`可以得到下面的输出，根据自己的需求输入指定指令即可

   ```
   Usage: ./fje -f <json file> -s <style> -i <icon family>
   <style>: rectangle or tree
   <icon family>: poker-face or json_defined
   ```

例如，输入下面的指令可以得到矩形风格，自定义图标族下的转换结果：

```
./fje -f ../input/example.json -s rectangle -i json_defined
```

