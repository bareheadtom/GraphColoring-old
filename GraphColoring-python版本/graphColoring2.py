
import numpy as np
import time
#初始化颜色分配，随机分配为k种颜色
def initialSolution(sol,k,n):
    sol = np.random.randint(0, k, size=(n))
    for i in range(n):
        if i<k:
            sol[i]=i
        else:
            sol[i]=np.random.randint(0,k,1)
    # sol[0] = 0
    # sol[2] = 0
    # sol[3] = 0
    # sol[1] = 1
    # sol[6] = 1
    # sol[7] = 1
    # sol[4] = 2
    # sol[5] = 2
    # sol[8] = 2

    # sol[0] = 0
    # sol[1] = 1
    # sol[2] = 1
    # sol[3] = 1
    # sol[4] = 1
    # sol[5] = 1
    # sol[6] = 0
    # sol[7] = 0
    # sol[8] = 1
    return sol
#初始化邻居颜色表
def initializeAdjacentColorTable(adjacent_Color_Table,edges,sol):
    for e in edges:
        row = e[1] - 1
        col = sol[e[2] - 1]
        Adjacent_Color_Table[row][col] += 1
        row = e[2] - 1
        col = sol[e[1] - 1]
        adjacent_Color_Table[row][col] += 1
#根据sol颜色分配表计算冲突f和冲突的边
def calculateFValueAndConfilictPares(edges,sol):
    f=0
    confilictPares=[]
    for e in edges:
        if sol[e[1] - 1] == sol[e[2] - 1]:
            #print("e", e)
            confilictPares.append((e[1]-1,e[2]-1))
            f = f + 1
    return f,confilictPares

#得到给定节点的所有相邻节点，用于更新相邻颜色表
def getAdjacentVertices(edges,vertice):
    adjacentVertices=[]
    for e in edges:
        #print(",",e)
        if e[1]==vertice:
            adjacentVertices.append(e[2]-1)
        elif e[2]==vertice:
            adjacentVertices.append(e[1]-1)
    #print("adjacentVertices", adjacentVertices)
    print("vertice,adjacentVertices",vertice-1,adjacentVertices)
    return adjacentVertices

# def ifExistImprovingMoves(confilictParesParam,adjacent_Color_Table,sol,n,k,taBuTenureTable,iterCur):
#     if len(confilictParesParam)==0:
#         return False
#     bestMove1,bestdeltValue1=findMove(adjacent_Color_Table,sol,n,k,taBuTenureTable,iterCur)
#     #print("bestMove", bestMove)
#     #print("bestdertValue", bestdeltValue)
#     if bestdeltValue1<0:
#         return True
#     else:
#         return False

def findMove(adjacent_Color_Table,sol,n,k,taBuTenureTable,iterCur):
    #print("k,n",k,n)
    bestMove = (0, 0, 0)
    #u, vi, vj = bestMove[0], bestMove[1], bestMove[2]
    bestdeltValue = 0
    bestTabuMove=(0,0,0)
    bestTabuDeltValue=0
    count=0
    deltList=[]
    tabuCount=0
    tabuDeltList=[]
    # print("bestMove",bestMove)
    # print("bestdertValue",bestdertValue)
    # print("confilictPares", confilictPares,"k",k)
    init=0
    for i in range(n):
        if adjacent_Color_Table[i][sol[i]] > 0:
            for color in range(k):
                if color != sol[i]:
                    #print("color",color)
                    bestMovePre = (i, sol[i], color)
                    u, vi, vj = bestMovePre[0], bestMovePre[1], bestMovePre[2]
                    #print(u,vi,vj)
                    bestdeltValuePre = adjacent_Color_Table[u][vj] - adjacent_Color_Table[u][vi]
                    #非禁忌移动
                    init+=1
                    if taBuTenureTable[i][color]<=iterCur:
                        if init==1:
                            bestMove=bestMovePre
                            bestdeltValue=bestdeltValuePre
                        if bestdeltValuePre<bestdeltValue:
                            #print(sol)
                            #print("非禁忌",i,sol[i],color)
                            count=0
                            bestdeltValue=bestdeltValuePre
                            bestMove = bestMovePre
                            bestdeltValue = bestdeltValuePre
                            count += 1
                            deltList.clear()
                            deltList.append([i, color])
                        elif bestdeltValuePre==bestdeltValue:
                            bestMove=bestMovePre
                            bestdeltValue=bestdeltValuePre
                            count+=1
                            deltList.append([i,color])
                    #禁忌移动
                    if taBuTenureTable[i][color]>iterCur:
                        if init==1:
                            bestTabuMove=bestMovePre
                            bestTabuDeltValue=bestdeltValuePre
                        if bestdeltValuePre<bestTabuDeltValue:
                            tabuCount=0
                            bestTabuDeltValue=bestdeltValuePre
                            bestTabuMoveMove = bestMovePre
                            bestTabuDeltValue = bestdeltValuePre
                            tabuCount += 1
                            tabuDeltList.clear()
                            tabuDeltList.append([i, color])
                        elif bestdeltValuePre==bestTabuDeltValue:
                            bestTabuMoveMove = bestMovePre
                            bestTabuDeltValue = bestdeltValuePre
                            tabuCount+=1
                            tabuDeltList.append([i,color])
    print("deltList",deltList)
    print("tabuDeltList",tabuDeltList)
    #全是禁忌移动

    if bestTabuDeltValue<Best_f-f and bestTabuDeltValue<bestdeltValue:
        print("禁忌解除**********************************")
        bestdeltValue=bestTabuDeltValue
        tmp=np.random.randint(0,255)%tabuCount#在相同的禁忌移动中随机选择一次移动
        u,vi,vj=tabuDeltList[tmp][0],sol[tabuDeltList[tmp][0]],tabuDeltList[tmp][1]
        bestMove=(u,vi,vj)
    elif len(deltList) == 0:
        #如果全是禁忌动作
            bestdeltValue = bestTabuDeltValue
            tmp = np.random.randint(0, 255) % tabuCount
            u, vi, vj = tabuDeltList[tmp][0], sol[tabuDeltList[tmp][0]], tabuDeltList[tmp][1]
            bestMove = (u, vi, vj)
    else:
        print("未禁忌解除")
        tmp = np.random.randint(0, 255) % count#在相同的非禁忌移动中随机选择一次移动
        print(sol)
        u, vi, vj = deltList[tmp][0], sol[deltList[tmp][0]], deltList[tmp][1]
        bestMove = (u, vi, vj)

    #


    #print("bestMove", bestMove)
    #print("bestdertValue", bestdeltValue)
    return bestMove,bestdeltValue

def makeMove(adjacent_Color_Table,sol,bestMove,bestdeltValue,taBuTenureTable,iterCur):
    global Best_f,f
    node = bestMove[0] + 1
    u,vi,vj=bestMove[0],bestMove[1],bestMove[2]
    # print("node",node)
    adjacentVertices = getAdjacentVertices(edges, node)
    # print("adjacentVertices",adjacentVertices)
    # bestMove=[0,0,1]
    #更新邻居颜色表
    for vertice in adjacentVertices:
        adjacent_Color_Table[vertice][bestMove[1]] -= 1
        adjacent_Color_Table[vertice][bestMove[2]] += 1
    #print("Adjacent_Color_Table updated", adjacent_Color_Table)
    #更新颜色分配表
    sol[u] = vj
    f, confilictPares = calculateFValueAndConfilictPares(edges, sol)
    #f=f+bestdeltValue
    #更新禁忌表
    taBuTenureTable[u][vi]=iterCur+f+np.random.randint(0,10,1)
    #taBuTenureTable[u][vi] = iterCur + f

    if f<Best_f:
        Best_f=f

    return f,confilictPares

#def ifSatisfiesTabuAspiration(bestTabuMove,bestdeltValue,bestTabuDeltValue,best_f):

#按行读取文件，空格分开
file=open("data/DSJC250.5.col")
#file=open("data/test.col")
n=0
e=0
#读取数据
num=0
edges=[]
for line in file:
    if line[0]=='p':
        list=line.split()
        #print(list)
        n=int(list[2])
        e=int(list[3])
    if line[0]=='e':
        num=num+1
        list=line.split()
        list[1],list[2]=int(list[1]),int(list[2])
        edges.append(list)
        #print(list)

k=28

print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) )
t1=time.time()
#图的描述
print("n",n," e",e,"num",num,"k",k)
#SLS 和 TS所需数据结构
Sol = np.random.randint(0, k, size=(n))
Sol=initialSolution(Sol,k,n)
print("initialSolution",Sol)
f,confilictPares=calculateFValueAndConfilictPares(edges,Sol)
#print("f",f)
#print("confilictPares",confilictPares)
BestSol=np.zeros((n))
Best_f=f
TaBuTenureTable=np.zeros((n,k))
#print(TaBuTenureTable)
Adjacent_Color_Table=np.zeros((n,k))
#print("Sol",Sol)
#print("edges",edges)
#初始化邻居表
initializeAdjacentColorTable(Adjacent_Color_Table,edges,Sol)
#print(Adjacent_Color_Table)
bestMove=()
bestdeltValue=0

#adjacentVertices=getAdjacentVertices(edges,1)
#print("adjacentVertices",adjacentVertices)
#初始化迭代次数为1
iterCur=1
while(f>0):
    #构建所有邻居
    print("iterCur",iterCur)
    print("Sol",Sol)
    #findMove
    bestMove,bestdeltValue=findMove(Adjacent_Color_Table,Sol,n,k,TaBuTenureTable,iterCur)
    print("bestMove", bestMove)
    print("bestdertValue",bestdeltValue)
    f=f+bestdeltValue
    f,confilictPares=makeMove(Adjacent_Color_Table,Sol,bestMove,bestdeltValue,TaBuTenureTable,iterCur)
    #print("Adjacent_Color_Tableupdated",Adjacent_Color_Table)
    #print("TaBuTenureTable",TaBuTenureTable)
    print('f,Best_f',f,Best_f)
    iterCur+=1
print(Sol)
print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) )
if f>0:
    print("not")
print("s",time.time()-t1)



