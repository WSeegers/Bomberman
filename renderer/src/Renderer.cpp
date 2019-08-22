#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer(/* args */) {
}

Renderer::~Renderer() {
}

void Renderer::init() {
  // Enable glew
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    std::cout << "failed to init GLEW: " << glewGetErrorString(err) << std::endl;
    throw ("GLEW failed");
  }
  std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
  glEnable(GL_DEPTH_TEST);

  //Wireframing
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  //Load objects into vram
  Model_st modelLoad;

  modelLoad.model = new Model("../../renderer/res/models/box/wall.obj");
  modelLoad.initialPos = glm::vec3(0.0f, 0.5f, 0.0f);
  modelLoad.initialRot = glm::vec4(0.0f, 1.0f, 0.0f,0.0f);
  modelLoad.initialScale = glm::vec3(0.5f);
  _models.push_back(modelLoad);

  modelLoad.model = new Model("../../renderer/res/models/wall/wall.obj");
  modelLoad.initialPos = glm::vec3(0.0f, 0.5f, 0.0f);
  modelLoad.initialRot = glm::vec4(0.0f, 1.0f, 0.0f,0.0f);
  modelLoad.initialScale = glm::vec3(0.5f);
  _models.push_back(modelLoad);

  // modelLoad.model = new Model("../../renderer/res/models/giraffe/10021_Giraffe_v04.obj");
  // modelLoad.initialPos = glm::vec3(0.0f);
  // modelLoad.initialRot = glm::vec4(1.0f, 0.0f, 0.0f, 270.0f);
  // modelLoad.initialScale = glm::vec3(0.01f);
  // _models.push_back(modelLoad);

  modelLoad.model = new Model("../../renderer/res/models/cowboy/model.dae");
  modelLoad.initialPos = glm::vec3(0.0f);
  modelLoad.initialRot = glm::vec4(1.0f, 0.0f, 0.0f, 270.0f);
  modelLoad.initialScale = glm::vec3(0.2f);
  _models.push_back(modelLoad);

  //compile shader programs
  _shader = new Shader("../../renderer/res/shaders/vertexShader.glsl", "../../renderer/res/shaders/fragmentShader.glsl");

  //build camera
  _camera = new Camera(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f);
}

void Renderer::player(sf::Window &window, const GameState &state)
{
  glm::mat4 model = glm::mat4(1.0f);
	sf::Vector2f playerPosition(state.player.position());
	playerPosition -= sf::Vector2f(0.5, 0.5);
  model = glm::translate(model, _models[playerModel].initialPos + glm::vec3(playerPosition.x, 0.0f, playerPosition.y));
  model = glm::scale(model, _models[playerModel].initialScale);
  model = glm::rotate(model, glm::radians(_models[playerModel].initialRot.w), glm::vec3(_models[playerModel].initialRot));
  _shader->setMat4("model", model);
  _models[playerModel].model->draw(*_shader);
}

void Renderer::map(sf::Window &window, const GameState &state)
{
	const Map &map = state.map;
	const sf::Vector2i &mapSize = map.size();
	Tile tile;
	sf::RectangleShape cell(sf::Vector2f(SCALE, SCALE));
	sf::CircleShape bomb(SCALE / 2);
	cell.setFillColor(sf::Color(250));
          name = unbreakableModel;
					break;
				case Tile::Destructible:
					name = breakableModel;
					cell.setFillColor(sf::Color(50, 150, 20));
					window.draw(cell);
					break;
				case Tile::Destructible:
					cell.setFillColor(sf::Color(50, 50, 150));
					window.draw(cell);
        model = glm::translate(model, _models[name].initialPos + glm::vec3(cellPosition.x, 0.0f, cellPosition.y));
        model = glm::scale(model, _models[name].initialScale);
        model = glm::rotate(model, glm::radians(_models[name].initialRot.w), glm::vec3(_models[name].initialRot));
        _shader->setMat4("model", model);
        _models[name].model->draw(*_shader);
			}
		}
	}
}

void Renderer::render(sf::Window &window, const GameState &state)
{
	sf::Vector2u size = window.getSize();
  glViewport(0, 0, size.x, size.y);
  glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader->use();
  glm::mat4 projection = glm::perspective(glm::radians(_camera->getZoom()), (float)size.x/(float)size.y, 0.1f,100.0f);
  glm::mat4 view = _camera->getViewMatrix();
  _shader->setMat4("projection", projection);
  _shader->setMat4("view", view);

	map(window, state);
	player(window, state);
	
	sf::Vector2f playerPosition(state.player.position());
	playerPosition -= sf::Vector2f(0.5, 0.5);
  _camera->setPosition(glm::vec3(playerPosition.x, 5.0f, playerPosition.y + 5.0f));
  _camera->setYaw(270.0f);
  _camera->setPitch(-45.0f);

  window.display();
}