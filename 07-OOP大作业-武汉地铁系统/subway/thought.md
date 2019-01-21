# 思路

## 一、系统组成

1. `MySQL`数据库`subway`
    - 表`station`: 保存站点信息
        - `name`站点名 : `String`
        - `id`站点ID : `int`
    - 表`route`: 保存地铁路线
        - `id`路线ID : `int`读取时分配
        - `name`路线名 : `String`
        - `path`途径站点: `String`
            - 站点ID，用逗号(`,`)分割，保存为字符串
            - 读取时`.split(",")`
    - 表`link`: 保存两个站点之间的路线信息
        - `from_id`起始站点ID : `int`
        - `to_id`到达站点ID : `int`
        - `belong_id`所属路线ID : `int`
        - `dist`距离 : `double`

2. 数据结构：
    - Station类:
        - 站点名 : `String`
        - 站点ID : `int`
    - Route类:
        - 路线ID : `int`
        - 路线名 : `String`
        - 途径站点: `int[]`，保存所有途径站点的ID
    - Link类:
        - 起始站点ID : `int`
        - 到达站点ID : `int`
        - 所属路线ID : `int`
        - 距离 : `double`

3. 系统结构：
    - `SubwaySystem`类:
        - `Map<Integer, Station> stations`
        - `List<List<Link>> links`
        - `Map<String, Route> routes`
        - 见下方
        - 所有交互方法
    - `Payment`类：
        - 抽象类
        - 传入距离，根据规则与支付方式计算金额
    - `RegularTicket`类：普通买票
        - `WuhanCard`类：继承`RegularTicket`，武汉通九折
    - `OneDayTicket`类：一日票

## 二、起始步骤

1. 从`subway.txt`中完全读取信息，存入`MySQL`(仅首次运行代码时执行)
2. 从`MySQL`中读取数据到代码数据结构
    - 表`station` -> `Map<Integer, Station> stations`，创建ID到站点实例的映射关系，这里是全代码中唯一获取站点名的方法，代码中其余部分站点均使用ID表示
    - 表`link` -> `List<List<Link>> links` 创建邻接链表
        - 使用邻接链表：两个相邻中转站(`Route`的交点)有不同的信息
    - 表`route` -> `Map<String, Route> routes` 创建路线名->路线实例的映射关系

## 三、解题思路

1. 给定站点名，返回经过该站点的所有路线的名称集合
    - 获取ID
    - 在`routes`中寻找包含该ID的路线，保存路线的名称

2. 给定线路名和终点方向，返回该路线中所有站点的顺序列表
    - 从`routes`获取路线实例
    - 判断方向
    - 利用`stations`打印输出

3. 给定起点站和终点站的名称，返回一条最短路径，该路径是一个从起点开始直到终点，所需要经过的所有站点的数组
    - 从`stations`获取ID
    - ~~利用`Dijkstra`算法寻找最短(长度最短)路~~
    - 利用`Floyd`算法寻找目标路径
        - 路径最短
        - 换乘最少
            - 思路：对换乘添加惩罚
    - 保存最短路径点与点之间的`Link`信息 -> `List<Link>`
    - 生成最短路径 -> `List<Integer>`
    - 利用`stations`打印输出

4. 当找到最短乘车路径后，我们需要把它以更方便的形式呈献给用户。请实现一个方法，将路径以简洁的形式打印至标准输出。
    - 利用上一问中返回的`List<Link>`
    - 利用`Link`类中“所属路线ID”属性处理转车情况
    - 输出

5. 对于给定路径，计算其对应的乘车费用(普通单程票)
    - 根据消费策略输出对应金额
    - 使用抽象类，实现`double pay(double distace)`接口

6. 对于同样的路径，计算使用武汉通和日票的乘客的票价（日票返回0元）
    - 简单输出

7. 添加图形界面
    - TODO