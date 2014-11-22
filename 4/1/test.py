# coding=utf-8
from Tree import *

Hua = Tree('Hua')

JuHua = Hua.insert(Tree('JuHua'))
LanHua = Hua.insert(Tree('LanHua'))

TieJuHua = Hua[JuHua].insert(Tree('TieJuHua'))
JuHuaTie = Hua[JuHua].insert(Tree('JuHuaTie'))

GangTieDaJuHua = Hua[TieJuHua].insert(Tree('GangTieDaJueHua'))
BaoJuHua = Hua[TieJuHua].insert(Tree('BaoJuHua'))

JuHuaCan = Hua[JuHuaTie].insert(Tree('JuHuaCan'))

XiaoLanHua = Hua[LanHua].insert(Tree('XiaoLanHua'))

MaoLiLan = Hua[XiaoLanHua].insert(Tree('MaoLiLan'))


print Hua
