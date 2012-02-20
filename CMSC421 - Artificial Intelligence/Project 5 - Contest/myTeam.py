# myTeam.py
# ---------
# Licensing Information: Please do not distribute or publish solutions to this
# project. You are free to use and extend these projects for educational
# purposes. The Pacman AI projects were developed at UC Berkeley, primarily by
# John DeNero (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# For more info, see http://inst.eecs.berkeley.edu/~cs188/sp09/pacman.html

from captureAgents import CaptureAgent
import random, time, util
from util import nearestPoint
from game import Directions
import game


#Helper classes and methods for A* Search
class Node:
  def __init__(self, state, action, cost, parent):
    self.state = state
    self.action = action
    self.cost = cost
    self.parent = parent
    
  def getPath(self):
    if self.parent == None: return []
    path = self.parent.getPath()
    return path + [self.action]
  
class FoodProblem:
    def __init__(self, gameState, agent):
       self.walls = gameState.getWalls()
       #self.start = (gameState.getPacmanPosition(), gameState.getFood())
       self.startState = gameState
       self.agent = agent
       self._expanded = 0
       
       
    def getStartState(self):
       return self.startState
    
    def isGoalState(self, state):
       return  self.agent.getFood(state).count() == 0

    def getSuccessors(self, state):
      successors = []
      self._expanded += 1
      actions = state.getLegalActions(self.agent.index)
      for action in actions:
        successors.append((state.generateSuccessor(self.agent.index, action), action, 1))
        
    #for direction in [Directions.NORTH, Directions.SOUTH, Directions.EAST, Directions.WEST]:
    #  x,y = state.getAgentPosition(self.agent.index)
    #  dx, dy = Actions.directionToVector(direction)
    #  nextx, nexty = int(x + dx), int(y + dy)
    #  if not self.walls[nextx][nexty]:
    #    nextFood = state[1].copy()
    #    nextFood[nextx][nexty] = False
    #    successors.append( ( ((nextx, nexty), nextFood), direction, 1) )
      return successors

    def getCostOfActions(self, actions):
      x,y= self.getStartState().getAgentPosition(self.agent.index)
      cost = 0
      for action in actions:
      # figure out the next state and see whether it's legal
        dx, dy = Actions.directionToVector(action)
        x, y = int(x + dx), int(y + dy)
        if self.walls[x][y]:
          return 999999
        cost += 1
      return cost
  


#################
# Team creation #
#################

def createTeam(firstIndex, secondIndex, isRed,
               first = 'TopAgent', second = 'BottomAgent'):
  """
  This function should return a list of two agents that will form the
  team, initialized using firstIndex and secondIndex as their agent
  index numbers.  isRed is True if the red team is being created, and
  will be False if the blue team is being created.

  As a potentially helpful development aid, this function can take
  additional string-valued keyword arguments ("first" and "second" are
  such arguments in the case of this function), which will come from
  the --redOpts and --blueOpts command-line arguments to capture.py.
  For the nightly contest, however, your team will be created without
  any extra arguments, so you should make sure that the default
  behavior is what you want for the nightly contest.
  """

  # The following line is an example only; feel free to change it.
  return [eval(first)(firstIndex), eval(second)(secondIndex)]

##########
# Agents #
##########

class MainAgent(CaptureAgent):

  def registerInitialState(self, gameState):
    """
    This method handles the initial setup of the
    agent to populate useful fields (such as what team
    we're on). 
    
    A distanceCalculator instance caches the maze distances
    between each pair of positions, so your agents can use:
    self.distancer.getDistance(p1, p2)

    IMPORTANT: This method may run for at most 15 seconds.
    """

    ''' 
    Make sure you do not delete the following line. If you would like to
    use Manhattan distances instead of maze distances in order to save
    on initialization time, please take a look at
    CaptureAgent.registerInitialState in captureAgents.py. 
    '''
    CaptureAgent.registerInitialState(self, gameState)

    ''' 
    Your initialization code goes here, if you need any.
    '''
    if self.red:
      CaptureAgent.registerTeam(self, gameState.getRedTeamIndices())
    else:
      CaptureAgent.registerTeam(self, gameState.getBlueTeamIndices())

    #Agents try to go to center with top or bottom bias
    self.goToCenter(gameState)


  #HELPER METHODS
  #Detects enemies that are visible
  def getEnemyPos(self, gameState):
    enemyPos = []
    for enemyI in self.getOpponents(gameState):
      pos = gameState.getAgentPosition(enemyI)
      #Will need inference if None
      if pos != None:
        enemyPos.append((enemyI, pos))
    return enemyPos

  #Closest enemies
  def enemyDist(self, gameState):
    pos = self.getEnemyPos(gameState)
    minDist = None
    if len(pos) > 0:
      minDist = float('inf')
      myPos = gameState.getAgentPosition(self.index)
      for i, p in pos:
        dist = self.getMazeDistance(p, myPos)
        if dist < minDist:
          minDist = dist
    return minDist

  #Is agent a pacman or a ghost?
  def inEnemyTerritory(self, gameState):
    return gameState.getAgentState(self.index).isPacman

  #The A*/heuristic code is my partners
  def aStarSearch(self, problem):
    startNode = Node(problem.getStartState(), None, 0, None)
    if problem.isGoalState(startNode.state): return []
    frontier = util.PriorityQueue()
    frontier.push(startNode, self.heuristic(startNode.state, problem))
    explored = set()
    while True:
      if frontier.isEmpty(): return None
      node = frontier.pop()
      if node.state in explored: continue
      if problem.isGoalState(node.state): return node.getPath()
      explored.add(node.state)
      children = problem.getSuccessors(node.state)
      for (st, act, cst) in children:
        child = Node(st, act, cst+node.cost, node)
        if child.state not in explored:
          frontier.push(child, self.heuristic(child.state, problem))

  def heuristic(self, state, problem):
    #position, foodGrid = state
    #food = foodGrid.asList()
    position = state.getAgentPosition(self.index)                  
    food = self.getFood(state).asList()
    walls = problem.walls

    heur = 0
    c = None
    for fd in food:
      #x = distances[fd][position]
      x = self.getMazeDistance(fd, position)
      if c == None or x < self.getMazeDistance(c, position): c = fd
    if c == None: return heur
    #heur = distances[c][position]
    heur = self.getMazeDistance(c, position)               
    if len(food) > 1:
      for fd in food:
        if fd != c:
          closest = 99999
          for nxt in food:
            dist = self.getMazeDistance(fd, nxt)            
            #dist = distances[fd][nxt]
            if nxt != fd and dist < closest:
              closest = dist
          heur+=closest
    return heur

  #/HELPER METHODS


  def chooseAction(self, gameState):
    """
    Picks among the actions with the highest Q(s,a).
    """
    # You can profile your evaluation time by uncommenting these lines
    start = time.time()

    agentPos = gameState.getAgentPosition(self.index)
    evaluateType = 'attack'

    #Start at start state, try to get to center then switch to offense
    if self.atCenter == False:
      evaluateType = 'start'

    if agentPos == self.center and self.atCenter == False:
      self.atCenter = True
      evaluateType = 'attack'

    enemyPos = self.getEnemyPos(gameState)
    if len(enemyPos) > 0:
      for enemyI, pos in enemyPos:
        #If we detect an enemy and are on home turf we go after them and defend home
        if self.getMazeDistance(agentPos, pos) < 6 and not self.inEnemyTerritory(gameState):
          evaluateType = 'defend'
          break

    actions = gameState.getLegalActions(self.index)
    values = [self.evaluate(gameState, a, evaluateType) for a in actions]
    #print 'eval time for agent %d: %.4f' % (self.index, time.time() - start)

    maxValue = max(values)
    bestActions = [a for a, v in zip(actions, values) if v == maxValue]

    return random.choice(bestActions)


  def getSuccessor(self, gameState, action):
    """
    Finds the next successor which is a grid position (location tuple).
    """
    successor = gameState.generateSuccessor(self.index, action)
    pos = successor.getAgentState(self.index).getPosition()
    if pos != nearestPoint(pos):
      # Only half a grid position was covered
      return successor.generateSuccessor(self.index, action)
    else:
      return successor


  def evaluate(self, gameState, action, evaluateType):
    """
    Computes a linear combination of features and feature weights
    """
    if evaluateType == 'attack':
      features = self.getFeaturesAttack(gameState, action)
      weights = self.getWeightsAttack(gameState, action)
    elif evaluateType == 'defend':
      features = self.getFeaturesDefend(gameState, action)
      weights = self.getWeightsDefend(gameState, action)
    elif evaluateType == 'start':
      features = self.getFeaturesStart(gameState, action)
      weights = self.getWeightsStart(gameState, action)

    return features * weights

  
  def getFeaturesAttack(self, gameState, action):
    features = util.Counter()
    successor = self.getSuccessor(gameState, action)
    features['successorScore'] = self.getScore(successor)

    myState = successor.getAgentState(self.index)
    myPos = myState.getPosition()

    #Compute distance to the nearest food
    foodList = self.getFood(successor).asList()
    if len(foodList) > 0: #This should always be True, but better safe than sorry
      minDistance = min([self.getMazeDistance(myPos, food) for food in foodList])
      features['distanceToFood'] = minDistance

    #Compute distance to ally agent (maximize distance between if in enemyTerritory)
 
    #Compute distance to enemy
    distEnemy = self.enemyDist(successor)
    if(distEnemy <= 4):
      features['danger'] = 1
    else:
      features['danger'] = 0  

    #Compute distance to capsule
    capsules = self.getCapsules(successor)
    if(len(capsules) > 0):
      minCapsuleDist = min([self.getMazeDistance(myPos, capsule) for capsule in capsules])
    else:
      minCapsuleDist = .1
      
    features['capsuleDist'] =  1.0 / minCapsuleDist

    #Don't want to do these things
    if action == Directions.STOP: features['stop'] = 1
    rev = Directions.REVERSE[gameState.getAgentState(self.index).configuration.direction]
    if action == rev: features['reverse'] = 1

    return features


  def getFeaturesDefend(self, gameState, action):
    features = util.Counter()
    successor = self.getSuccessor(gameState, action)

    myState = successor.getAgentState(self.index)
    myPos = myState.getPosition()

    #Computes distance to invaders we can see
    enemies = [successor.getAgentState(i) for i in self.getOpponents(successor)]
    invaders = [a for a in enemies if a.isPacman and a.getPosition() != None]
    #Find # of invaders
    features['numInvaders'] = len(invaders)
    if len(invaders) > 0:
      dists = [self.getMazeDistance(myPos, a.getPosition()) for a in invaders]
      #Find closest invader
      features['invaderDistance'] = min(dists)

    if action == Directions.STOP: features['stop'] = 1
    rev = Directions.REVERSE[gameState.getAgentState(self.index).configuration.direction]
    if action == rev: features['reverse'] = 1

    return features

  def getFeaturesStart(self, gameState, action):
    features = util.Counter()
    successor = self.getSuccessor(gameState, action)

    myState = successor.getAgentState(self.index)
    myPos = myState.getPosition()

    dist = self.getMazeDistance(myPos, self.center)
    features['distToCenter'] = dist
    if myPos == self.center:
      features['atCenter'] = 1
    return features


  def getWeightsAttack(self, gameState, action):
    return {'successorScore': 100, 'danger': -400, 'distanceToFood': -1, 'stop': -2000, 'reverse': -20, 'capsuleDist': 3}


  def getWeightsDefend(self, gameState, action):
    return {'numInvaders': -1000, 'invaderDistance': -50, 'stop': -2000, 'reverse': -20}


  def getWeightsStart(self, gameState, action):
    return {'distToCenter': -1, 'atCenter': 1000}
  

class TopAgent(MainAgent):

  def goToCenter(self, gameState):
    locations = []
    self.atCenter = False
    x = gameState.getWalls().width / 2
    y = gameState.getWalls().height / 2
    #0 to x-1 and x to width
    if self.red:
      x = x - 1
    self.center = (x, y)
    maxHeight = gameState.getWalls().height

    #look for locations to move to that are not walls (favor top positions)
    for i in xrange(maxHeight - y):
      if not gameState.hasWall(x, y):
        locations.append((x, y))
      y = y + 1

    myPos = gameState.getAgentState(self.index).getPosition()
    minDist = float('inf')
    minPos = None

    for location in locations:
      dist = self.getMazeDistance(myPos, location)
      if dist <= minDist:
        minDist = dist
        minPos = location
    
    self.center = minPos


class BottomAgent(MainAgent):

  def goToCenter(self, gameState):
    locations = []
    self.atCenter = False
    x = gameState.getWalls().width / 2
    y = gameState.getWalls().height / 2
    #0 to x-1 and x to width
    if self.red:
      x = x - 1
    self.center = (x, y)
    
    #look for locations to move to that are not walls (favor bot positions)
    for i in xrange(y):
      if not gameState.hasWall(x, y):
        locations.append((x, y))
      y = y - 1

    myPos = gameState.getAgentState(self.index).getPosition()
    minDist = float('inf')
    minPos = None

    for location in locations:
      dist = self.getMazeDistance(myPos, location)
      if dist <= minDist:
        minDist = dist
        minPos = location
    
    self.center = minPos












