#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "obj.h"
#include "aabb_collide.h"

namespace demo2d {

enum class GAMESTATE { PLAYING, WON, LOST };

GAMESTATE gamestate = GAMESTATE::PLAYING;

struct Player {
  float speed;
  float jump_power;
  obj body;
  bool left = false, right = false, jump = false;
  bool falling = true;
};

// assets
std::vector<obj> objects = {
  { glm::vec3(-400, -300, -1), glm::vec3(100,50,1), glm::vec3(.4f) },
  { glm::vec3(-200, -300, -1), glm::vec3(100,50,1), glm::vec3(.4f) },
  { glm::vec3(0,   -200, -1), glm::vec3(100, 10,1), glm::vec3(.55f) },
  { glm::vec3(200, -300, -1), glm::vec3(100, 50,1), glm::vec3(.4f) },
  { glm::vec3(400, -300, -1), glm::vec3(100, 50,1), glm::vec3(.4f) }
};

Player player = { 165.f, 140.f, glm::vec3(-475, -225, -1), glm::vec3(15,15,1), glm::vec3(.3, .3, .75) };

obj goal = { glm::vec3(475, -225, -1), glm::vec3(5,5,1), glm::vec3(.3, .8, .3) };

std::vector<obj> lost_display = {
  { glm::vec3(0, 0, -1), glm::vec3(25, 100,1), glm::vec3(.7f,.0f, .1f), glm::vec3(0, 0, glm::radians(45.f)) },
  { glm::vec3(0, 0, -1), glm::vec3(25, 100,1), glm::vec3(.7f,.0f, .1f), glm::vec3(0, 0, glm::radians(-45.f)) }
};

std::vector<obj> won_display = {
  { glm::vec3(-81, -25, -1), glm::vec3(25, 50,1), glm::vec3(.0f, .7f, .1f), glm::vec3(0, 0, glm::radians(45.f)) },
  { glm::vec3(0, 0, -1), glm::vec3(25, 100,1), glm::vec3(.0f, .7f, .1f), glm::vec3(0, 0, glm::radians(-45.f)) }
};

void Reset() {
  player = { 165.f, 140.f, glm::vec3(-475, -225, -1), glm::vec3(15,15,1), glm::vec3(.3, .3, .75) };
  gamestate = GAMESTATE::PLAYING;
}


void Update(float dt) {
  // update gamestate
  const float end_display_length = 3.f;
  static float end_display_timer = 0.f;
  switch (gamestate) {
  case GAMESTATE::PLAYING:
    break;
  case GAMESTATE::WON:
  case GAMESTATE::LOST:
    end_display_timer += dt;
    if (end_display_timer > end_display_length) {
      end_display_timer = 0.f;
      Reset();
    }
    return;
  }

  // save details before update
  obj prev_player_body = player.body;

  // jump logic
  static float jump_timer = 0.f;
  if (player.jump && !player.falling) {
    jump_timer += dt;
    if (jump_timer < .6f) {
      player.body.location.y += player.jump_power * dt;
    } else {
      player.falling = true;
      jump_timer = 0.f;
    }
  }

  // falling or gravity logic
  static float fall_timer = 0.f;
  static float last_fall_velocity = 0.f;
  if (player.falling) {
    static const float grav = 4.1f;
    fall_timer += dt;
    player.body.location.y -= grav * fall_timer;
    last_fall_velocity = grav * fall_timer;
  } else {
    fall_timer = 0.f;
  }



  // move left or right
  if (player.left) {
    player.body.location.x -= player.speed * dt;
  }

  if (player.right) {
    player.body.location.x += player.speed * dt;
  }


  // check for new collisions
  if (player.left || player.right || player.jump || player.falling) {

    // check grounding
    bool on_something = false;
    if (!player.jump && !player.falling && (player.left || player.right))
    {
      obj feet = player.body;
      feet.location.y -= last_fall_velocity;
      for (const auto& o : objects) {
        if (CollidesWith(feet, o)) {
          on_something = true;
        }
      }
      if (!on_something && !player.jump) {
        player.falling = true;
      }
    }

    // check colliding
    for (const auto& o : objects) {
      if (CollidesWith(player.body, o)) {
        //printf("collided\n");

        if (player.falling) {
          player.body.location.y = prev_player_body.location.y;
          player.falling = false;
          jump_timer = 0.f;
        }

        if (player.left || player.right) {
          player.body.location.x = prev_player_body.location.x;
        }
        break;
      }
    }
  }

  // check end game conditions
  if (CollidesWith(player.body, goal)) {
    gamestate = GAMESTATE::WON;
    //std::cout << "won!\n";
    return;
  }

  if (player.body.location.y < -400) {
    gamestate = GAMESTATE::LOST;
    //std::cout << "lost!\n";
  }
}

void PlayerControls(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    player.left = true;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
    player.left = false;
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    player.right = true;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
    player.right = false;
  }

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    if (!player.jump) {
      player.jump = true;
    }
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
    if (player.jump) {
      player.jump = false;
      if (!player.falling)
        player.falling = true;
    }
  }
}

// draw game stuff
void Render(const std::vector<DrawStripDetails>& drawdetails) {
  switch (gamestate) {
  case GAMESTATE::PLAYING:
    for (const auto& ob : objects) {
      _2d_shader->SetMat4("uModelMatrix", glm::scale(glm::translate(glm::mat4(1), ob.location), ob.scale));
      _2d_shader->SetVec3("uColor", ob.color);
      DrawStrip(drawdetails);
    }

    _2d_shader->SetMat4("uModelMatrix", glm::scale(glm::translate(glm::mat4(1), player.body.location), player.body.scale));
    _2d_shader->SetVec3("uColor", player.body.color);
    DrawStrip(drawdetails);

    _2d_shader->SetMat4("uModelMatrix", glm::scale(glm::translate(glm::mat4(1), goal.location), goal.scale));
    _2d_shader->SetVec3("uColor", goal.color);
    DrawStrip(drawdetails);
    break;

  case GAMESTATE::WON:
    for (const auto& wi : won_display) {
      _2d_shader->SetMat4("uModelMatrix", glm::scale(glm::rotate(glm::translate(glm::mat4(1), wi.location), wi.rotation.z, glm::vec3(0, 0, 1)), wi.scale));
      _2d_shader->SetVec3("uColor", wi.color);
      DrawStrip(drawdetails);
    }
    break;

  case GAMESTATE::LOST:
    for (const auto& lo : lost_display) {
      _2d_shader->SetMat4("uModelMatrix", glm::scale(glm::rotate(glm::translate(glm::mat4(1), lo.location), lo.rotation.z, glm::vec3(0, 0, 1)), lo.scale));
      _2d_shader->SetVec3("uColor", lo.color);
      DrawStrip(drawdetails);
    }
    break;

  }

}

} // end namespace demo2d
