# search.py
# ---------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

"""
In search.py, you will implement generic search algorithms which are called 
by Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
  """
  This class outlines the structure of a search problem, but doesn't implement
  any of the methods (in object-oriented terminology: an abstract class).
  
  You do not need to change anything in this class, ever.
  """
  
  def getStartState(self):
     """
     Returns the start state for the search problem 
     """
     util.raiseNotDefined()
    
  def isGoalState(self, state):
     """
       state: Search state
    
     Returns True if and only if the state is a valid goal state
     """
     util.raiseNotDefined()

  def getSuccessors(self, state):
     """
       state: Search state
     
     For a given state, this should return a list of triples, 
     (successor, action, stepCost), where 'successor' is a 
     successor to the current state, 'action' is the action
     required to get there, and 'stepCost' is the incremental 
     cost of expanding to that successor
     """
     util.raiseNotDefined()

  def getCostOfActions(self, actions):
     """
      actions: A list of actions to take
 
     This method returns the total cost of a particular sequence of actions.  The sequence must
     be composed of legal moves
     """
     util.raiseNotDefined()
           

def tinyMazeSearch(problem):
  """
  Returns a sequence of moves that solves tinyMaze.  For any other
  maze, the sequence of moves will be incorrect, so only use this for tinyMaze
  """
  from game import Directions
  s = Directions.SOUTH
  w = Directions.WEST
  return  [s,s,w,s,w,w,s,w]

def pathConstructor(goal, dictionary):
  #use dictionary to lookup the previous nodes, reconstructing list backwards
  from game import Directions
  path = []
  currentNode = goal
  while(currentNode != None):
    path.append(currentNode[1])
    currentNode = dictionary[currentNode]
  path.reverse()
  return path

def depthFirstSearch(problem):
  """
  Search the deepest nodes in the search tree first [p 85].
  
  Your search algorithm needs to return a list of actions that reaches
  the goal.  Make sure to implement a graph search algorithm [Fig. 3.7].
  
  To get started, you might want to try some of these simple commands to
  understand the search problem that is being passed in:
  
  print "Start:", problem.getStartState()
  print "Is the start a goal?", problem.isGoalState(problem.getStartState())
  print "Start's successors:", problem.getSuccessors(problem.getStartState())
  """
  "*** YOUR CODE HERE ***"
  from util import Stack
  
  stack = Stack()
  exploredSet = set()
  pathConstructDict = {}
  
  #print "Start's successors:", problem.getSuccessors(problem.getStartState())

  #add start to exploredSet, and check if it is the goal 
  exploredSet.add(problem.getStartState())
  if(problem.isGoalState(problem.getStartState())):
    return []
    
  for successor in problem.getSuccessors(problem.getStartState()):
    #print successor
    stack.push((successor, None))

  while(not stack.isEmpty()):
    expansion = stack.pop()
    if(expansion[0][0] in exploredSet):
      continue

    exploredSet.add(expansion[0][0])
    pathConstructDict[expansion[0]] = expansion[1]

    if(problem.isGoalState(expansion[0][0])):
      return pathConstructor(expansion[0], pathConstructDict)

    for successor in problem.getSuccessors(expansion[0][0]):
      stack.push((successor, expansion[0]))
    
  #util.raiseNotDefined()

def breadthFirstSearch(problem):
  "Search the shallowest nodes in the search tree first. [p 81]"
  "*** YOUR CODE HERE ***"
  from util import Queue
  
  queue = Queue()
  exploredSet = set()
  pathConstructDict = {}
  
  #print "Start's successors:", problem.getSuccessors(problem.getStartState())

  #add start to exploredSet, and check if it is the goal 
  exploredSet.add(problem.getStartState())
  if(problem.isGoalState(problem.getStartState())):
    return []
    
  for successor in problem.getSuccessors(problem.getStartState()):
    #print successor
    queue.push((successor, None))

  while(not queue.isEmpty()):
    expansion = queue.pop()
    if(expansion[0][0] in exploredSet):
      continue

    exploredSet.add(expansion[0][0])
    pathConstructDict[expansion[0]] = expansion[1]

    if(problem.isGoalState(expansion[0][0])):
      return pathConstructor(expansion[0], pathConstructDict)

    for successor in problem.getSuccessors(expansion[0][0]):
      queue.push((successor, expansion[0]))
  #util.raiseNotDefined()
      
def uniformCostSearch(problem):
  "Search the node of least total cost first. "
  "*** YOUR CODE HERE ***"
  from util import PriorityQueue
  
  pathConstructDict = {}
  priorityQueue = PriorityQueue()
  costToNode = {}
  
  for successor in problem.getSuccessors(problem.getStartState()):
    priorityQueue.push((successor, None), successor[2]) #push successor and its priority is its path cost

  costToNode[problem.getStartState()] = 0

  while(not priorityQueue.isEmpty()):
    expansion = priorityQueue.pop()
    pathConstructDict[expansion[0]] = expansion[1]

    if(expansion[1] != None):
      costToNode[expansion[0][0]] = costToNode[expansion[1][0]] + expansion[0][2]
    else:
      costToNode[expansion[0][0]] = expansion[0][2]

    if(problem.isGoalState(expansion[0][0])):
      return pathConstructor(expansion[0], pathConstructDict)

    for successor in problem.getSuccessors(expansion[0][0]):
      if(successor[0] not in costToNode):
        priorityQueue.push((successor, expansion[0]), costToNode[expansion[0][0]] + successor[2])

  return None
  #util.raiseNotDefined()

def nullHeuristic(state, problem=None):
  """
  A heuristic function estimates the cost from the current state to the nearest
  goal in the provided SearchProblem.  This heuristic is trivial.
  """
  return 0

def aStarSearch(problem, heuristic=nullHeuristic):
  "Search the node that has the lowest combined cost and heuristic first."
  "*** YOUR CODE HERE ***"

  #A* is just UCS with g(n) + h(n)
  from util import PriorityQueue
  
  pathConstructDict = {}
  priorityQueue = PriorityQueue()
  costToNode = {}
  
  for successor in problem.getSuccessors(problem.getStartState()):
    priorityQueue.push((successor, None), successor[2] + heuristic(successor[0], problem)) #push successor and its priority is its path cost for a* it is g(n) + h(n)

  costToNode[problem.getStartState()] = 0

  while(not priorityQueue.isEmpty()):
    expansion = priorityQueue.pop()
    pathConstructDict[expansion[0]] = expansion[1]

    if(expansion[1] != None):
      costToNode[expansion[0][0]] = costToNode[expansion[1][0]] + expansion[0][2]
    else:
      costToNode[expansion[0][0]] = expansion[0][2]

    if(problem.isGoalState(expansion[0][0])):
      return pathConstructor(expansion[0], pathConstructDict)

    for successor in problem.getSuccessors(expansion[0][0]):
      if(successor[0] not in costToNode):
        priorityQueue.push((successor, expansion[0]), costToNode[expansion[0][0]] + successor[2] + heuristic(successor[0], problem))

  return None
  #util.raiseNotDefined()
    
  
# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
