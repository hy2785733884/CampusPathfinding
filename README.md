# 校园道路路径规划系统 —— A* vs JPS 算法性能对比

## 项目简介

基于 C++ 和 EasyX 图形库实现的寻路算法可视化对比系统。在同一校园网格地图上运行 A* 算法和 JPS（Jump Point Search）算法，通过图形化界面直观对比两种算法的搜索空间和路径结果，并使用 C++ `chrono` 库进行高精度性能计时。

## 算法说明

- **A\***：经典的启发式搜索算法，使用八方向 Octile 距离作为启发函数
- **JPS（Jump Point Search）**：A* 的优化变体，通过"跳点"剪枝大幅减少搜索空间中的展开节点数

## 技术栈

- 语言：C++17
- 图形库：EasyX
- 开发环境：Visual Studio 2022
- 版本控制：Git

## 构建与运行

### 环境要求

- Visual Studio 2022（含"使用 C++ 的桌面开发"工作负载）
- EasyX 图形库（https://easyx.cn/）

### 编译运行

1. 用 VS 打开 `CampusPathfinding.sln`
2. 确认解决方案配置为 `Debug | x64`
3. 按 `F5` 编译运行

### 自定义地图

编辑项目根目录下的 `map.txt`：

- `#` = 障碍物
- `.` 或空格 = 可通行区域
- `S` = 起点
- `G` = 终点

## 效果展示

程序运行后将以图形窗口展示：

- 灰色方块：障碍物（建筑物）
- 浅蓝色区域：A* 算法搜索空间
- 浅红色区域：JPS 算法搜索空间
- 蓝色粗线：A* 找到的路径
- 红色细线：JPS 找到的路径
- 底部文字：两种算法的耗时与节点展开数对比

## 项目结构


  CampusPathfinding/
  ├── maps/
  │   ├── map_campus.txt
  │   ├── map_maze.txt
  │   └── map_open.txt
  ├── src/
  │   ├── main.cpp
  │   ├── utils.h
  │   ├── utils.cpp
  │   ├── astar.h
  │   ├── astar.cpp
  │   ├── jps.h
  │   ├── jps.cpp
  │   ├── visualization.h
  │   └── visualization.cpp
  ├── CampusPathfinding.sln
  ├── CampusPathfinding.vcxproj
  ├── CampusPathfinding.vcxproj.filters
  ├── .gitignore
  └── README.md
