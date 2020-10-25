# GraphColoring Tabu Search Algorithm: A Case Study on  Graph Coloring realized by Python基于禁忌搜索实现的图着色算法，python实现
# data:
##   存放算例，
# readMe：
##   有第一列为算例文件，第二列为算例的输出结果，第三列为实际该算例成功着色的迭代次数
# 函数：
###   def initialSolution(sol,k,n):初始化图着色
###   def initializeAdjacentColorTable(adjacent_Color_Table,edges,sol):根据边和当前图着色情况生成邻接着色表
###   def calculateFValueAndConfilictPares(edges,sol):计算当前着色情况的f值和冲突边
###   def getAdjacentVertices(edges,vertice):获得指定节点的相邻节点
###   def findMove(adjacent_Color_Table,sol,n,k,taBuTenureTable,iterCur):找到一次最优移动
###   def makeMove(adjacent_Color_Table,sol,bestMove,bestdeltValue,taBuTenureTable,iterCur):执行最优移动
# 运算结果：
   算例文件名 |   最少着色颜色数      |     迭代次数 |  运算时间 
   ------------|-----------------|----------------|--------------
   DSJC125.1	    |         5      |          3440 |25.7s  
   DSJC125.5	    |         17       |          12972 |207.9s
   DSJC125.9	     |        44      |           13333  | 305.3s  
   DSJC250.1	     |        8      |            14835  |  202s
   DSJC250.5	      |       28
   DSJC250.9	       |      72
   DSJC500.1	      |       12
   DSJC500.5	       |      49,48,47

# 感想
通过这次图着色算法，使我初步了解了启发式优化。发现实现过程还是十分有趣的，比如中间也遇到过一些问题，在禁忌搜索过程中，遇到禁忌移动和非禁忌移动，当没有非禁忌移动时，却不满足禁忌解除的条件时，我们的解决方法有适当减小每次的禁忌值，或者直接选择最好的禁忌移动即可。虽然python实现比较简洁，但是算法运行过程中发现python的运行速度还是不如c语言的，打算下次运用c语言实现。相信自己有能力并且能一直能在这个方向做下去。
