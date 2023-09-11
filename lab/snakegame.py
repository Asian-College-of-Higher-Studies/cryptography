import pygame
import random
import sys

# Initialize Pygame
pygame.init()

# Constants
WIDTH, HEIGHT = 400, 400
GRID_SIZE = 20
GRID_WIDTH = WIDTH // GRID_SIZE
GRID_HEIGHT = HEIGHT // GRID_SIZE
SNAKE_SPEED = 10
SNAKE_SPEED_LEVEL2 = 15  # Increased speed for level 2
LEVEL_CHANGE_SCORE = 10

# Colors
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BRICK_RED = (255, 0, 0)  # Color for the wall bricks
SNAKE_HEAD_COLOR = (0, 0, 255)  # Color for the snake's head
count = 0
level = 1  # Initial level

# Directions
UP = (0, -1)
DOWN = (0, 1)
LEFT = (-1, 0)
RIGHT = (1, 0)

# Create the screen
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Snake Game")

# Initialize the Snake with an even larger initial size
snake = [(GRID_WIDTH // 2, GRID_HEIGHT // 2)] * 10  # Snake starts with 10 segments
snake_direction = RIGHT

try:
    apple_img = pygame.image.load("apple.png")
    apple_img = pygame.transform.scale(apple_img, (GRID_SIZE, GRID_SIZE))
except pygame.error as e:
    print("Error loading the apple image:", e)
    sys.exit(1)

# Function to generate a random position for the food outside the wall
def generate_food():
    while True:
        food_position = (random.randint(1, GRID_WIDTH - 2), random.randint(1, GRID_HEIGHT - 11))
        if food_position not in walls:
            return food_position

# Create walls on all sides of the screen
walls = set()
for x in range(GRID_WIDTH):
    walls.add((x, 0))
    walls.add((x, GRID_HEIGHT - 1))
for y in range(1, GRID_HEIGHT - 1):
    walls.add((0, y))
    walls.add((GRID_WIDTH - 1, y))

# Initialize the food
food = generate_food()

# Increase the food size
FOOD_SIZE = 20

# Font for the score and level display
font = pygame.font.Font(None, 24)

# Function to display the score and level on the left wall
def display_info(score, current_level):
    score_text = font.render(f"Score: {score}", True, WHITE)
    level_text = font.render(f"Level: {current_level}", True, WHITE)
    
    # Position the score and level text on the left wall
    score_position = (1, 1)
    level_position = (1, 2)  # Adjust the vertical position as needed
    
    screen.blit(score_text, (score_position[0] * GRID_SIZE, score_position[1] * GRID_SIZE))
    screen.blit(level_text, (level_position[0] * GRID_SIZE, level_position[1] * GRID_SIZE))

# Function to check collision with walls and bricks
def check_collision(position):
    return position in walls

# Game loop
clock = pygame.time.Clock()
game_over = False

while not game_over:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            game_over = True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP and snake_direction != DOWN:
                snake_direction = UP
            elif event.key == pygame.K_DOWN and snake_direction != UP:
                snake_direction = DOWN
            elif event.key == pygame.K_LEFT and snake_direction != RIGHT:
                snake_direction = LEFT
            elif event.key == pygame.K_RIGHT and snake_direction != LEFT:
                snake_direction = RIGHT

    # Move the Snake
    if level == 1:
        snake_speed = SNAKE_SPEED
    elif level == 2:
        snake_speed = SNAKE_SPEED_LEVEL2

    if count >= LEVEL_CHANGE_SCORE and level == 1:
        level = 2
        snake_speed = SNAKE_SPEED_LEVEL2

    if count < LEVEL_CHANGE_SCORE and level == 2:
        level = 1
        snake_speed = SNAKE_SPEED

    new_head = (snake[0][0] + snake_direction[0], snake[0][1] + snake_direction[1])
    snake.insert(0, new_head)

    # Check for collisions with food
    if snake[0] == food:
        food = generate_food()
        count += 1

    else:
        snake.pop()

    # Check for collisions with the wall or itself
    if (
        snake[0][0] < 0
        or snake[0][0] >= GRID_WIDTH
        or snake[0][1] < 0
        or snake[0][1] >= GRID_HEIGHT
        or snake[0] in snake[1:]
        or check_collision(snake[0])
    ): 
        print("Total score:", count)
        game_over = True

    # Clear the screen
    screen.fill((0, 0, 0))

    # Draw the walls
    for wall in walls:
        pygame.draw.rect(screen, BRICK_RED, (wall[0] * GRID_SIZE, wall[1] * GRID_SIZE, GRID_SIZE, GRID_SIZE))

    # Draw the Snake
    for i, segment in enumerate(snake):
        if i == 0:  # Head
            # Draw a smaller head
            head_rect = pygame.Rect(
                segment[0] * GRID_SIZE + 2,
                segment[1] * GRID_SIZE + 2,
                GRID_SIZE - 4,
                GRID_SIZE - 4,
            )
            pygame.draw.rect(screen, SNAKE_HEAD_COLOR, head_rect)
            # Draw the eyes
            eye_radius = 3
            left_eye_pos = (segment[0] * GRID_SIZE + 4, segment[1] * GRID_SIZE + 4)
            right_eye_pos = (segment[0] * GRID_SIZE + GRID_SIZE - 7, segment[1] * GRID_SIZE + 4)
            pygame.draw.circle(screen, WHITE, left_eye_pos, eye_radius)
            pygame.draw.circle(screen, WHITE, right_eye_pos, eye_radius)
        else:  # Body
            pygame.draw.rect(
                screen, GREEN, (segment[0] * GRID_SIZE, segment[1] * GRID_SIZE, GRID_SIZE, GRID_SIZE)
            )
    
    # Draw the food
    screen.blit(apple_img, (food[0] * GRID_SIZE, food[1] * GRID_SIZE))

    # Display the score and level on the left wall
    display_info(count, level)

    # Update the display
    pygame.display.flip()

    # Control game speed
    clock.tick(snake_speed)

# Quit Pygame
pygame.quit()
