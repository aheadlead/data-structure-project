# coding=utf-8

import sys
import json
import Queue

'''实现一个简单的公交系统。
不考虑票价。'''

class Station(object):
    def __init__(self, stationName):
        self.name = stationName
        self.neighbors = []
    
    def addNeighbor(self, neighbor, linename):
        self.neighbors.append((neighbor, linename))

class BusSystem(object):
    def __init__(self):
        self.stations = {}

    def addStation(self, station):
        assert not self.stations.has_key(station.name), station.name
        self.stations[station.name] = station
        
    def addLine(self, line, name):
        line = [self.stations[stationName] for stationName in line]
        for index in xrange(0,len(line)-1): # 建立站点之间的关系
            line[index].addNeighbor(line[index+1], name)
            line[index+1].addNeighbor(line[index], name)

    def findWayByStationName(self, departure, arrival):
        # Floodfill

        # 清空标号
        for stationName, station in self.stations.iteritems():
            station.label = None # None 表示这个站点尚未访问
            station.inQueue = False

        q = Queue.Queue()
        q.put(self.stations[departure])
        self.stations[departure].inQueue = True
        self.stations[departure].label = 0
        
        ans = []

        while True:
            station = q.get()

            if station == self.stations[arrival]: # 如果找到终点了
                while station != self.stations[departure]: # 往前追溯
                    for neighbor, linename in station.neighbors:
                        if neighbor.label != None and neighbor.label+1 == station.label:
                            # 说明 station 从 neighbor 转移而来
                            ans.append((station, linename)) # 加入答案列表
                            station = neighbor
                ans.append((station, None)) # 添加起点
                ans.reverse() # 翻转回来，因为添加的时候是反向添加的
                break
            
            for neighborStation, line in station.neighbors:
                if neighborStation.label == None: # 如果此站点尚未访问
                    q.put(neighborStation)
                    neighborStation.inQueue = True
                    neighborStation.label = station.label+1
        
        return ans

def main():
    bs = BusSystem()
    
    with open("njmetro.json", "r") as h:
        jsondata = json.loads("".join(h.readlines()))
        
    for stationFromJson in jsondata["station"]:
        bs.addStation(Station(stationFromJson.encode("utf-8")))
    
    for lineFromJson in jsondata["lines"]:
        bs.addLine(name=lineFromJson["name"].encode("utf-8"), \
                line=[s.encode("utf-8") for s in lineFromJson["line"]])

    while True:
        D = raw_input("出发地 ")
        if not bs.stations.has_key(D):
            print "没有这样的出发地。"
            continue

        A = raw_input("到达地 ")
        if not bs.stations.has_key(A):
            print "没有这样的到达地。"
            continue

        ans = bs.findWayByStationName(D, A)
        if [] == ans:
            print "没有找到路。"
        else:
            if 1 == len(ans):
                print "出发地就是到达地呀！"
            else:
                print "在 " + ans[0][0].name,
                sys.stdout.flush()
                print "上", ans[1][1].decode("utf-8"), "，经"
                for index in xrange(1, len(ans)-1):
                    if ans[index+1][1] == ans[index][1]:
                        print "\t" + ans[index][0].name
                    else:
                        print "\t在" + ans[index][0].name + "换乘" + \
                            ans[index+1][1]
                print "最后在" + ans[-1][0].name + "下车。"

        raw_input("任意键继续")

if __name__ == "__main__":
    main()
