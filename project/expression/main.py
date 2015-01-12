#!/usr/bin/env python
# coding=utf-8

'''表达式求值。'''

import re

def main():
    rawExpression = raw_input(">>> ")
    
    re.sub("^\(?P<num>)d+$", "
