import sys
import ast

def RenderIdent( i ):
    return "@%d" % i

def RenderInt( i ):
    return "#%d" % i

def RenderFloat( f ):
    return "^%f" % f

def RenderList( l ):
    return "[ "+" ".join(l)+" ]"

def RenderNode( n, t, l ):
    return ":"+str(n)+" "+t+" "+" ".join(l)

def RenderAssign( n, v ):
    return n+" "+v

def RenderString(ss):
    ss = ss.replace("\\", "\\\\") # do this first, otherwise it picks up the backslashes from the other escapes
    ss = ss.replace("\n", "\\n")
    ss = ss.replace("\t", "\\t")
    ss = ss.replace("\r", "\\r")
    ss = ss.replace("\"", "\\\"")
    ss = ss.replace(" ", "\\x20")
    return "\""+ss+"\"";
    
def RenderField(field):
    global max_index
    if field is None:
        s = "NULL"
    elif type(field) is str:
        s = RenderString(field)
    elif type(field) is int:
        s = RenderInt(field)
    elif type(field) is float:
        s = RenderFloat(field)
    elif type(field) is bool:
        s = "TRUE" if field else "FALSE"
    elif type(field) is list:
        elementnames = [RenderField(elt) for elt in field]
        s = RenderList(elementnames)
    else: # reference to another node
        max_index += 1 # allocate an index for it
        s = RenderIdent(max_index) # create its token
        FlatDumpTree(field, max_index) # Render it
    return s

def FlatDumpTree(node, my_index):
	global max_index
	nodename=node.__class__.__name__
	childnames = [RenderAssign(name,RenderField(child)) for (name, child) in ast.iter_fields(node)]
	if 'lineno' in node.__dict__: 
		lineno = node.__dict__['lineno']
	else:
		lineno = 0
	print RenderAssign(RenderIdent(my_index), RenderNode(lineno, nodename, childnames))
    
source=sys.stdin.read()
tree=ast.parse(source)
global max_index
max_index = 0
FlatDumpTree(tree, max_index)

