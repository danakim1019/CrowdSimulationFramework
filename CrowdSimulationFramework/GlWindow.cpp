#include "GlWindow.h"

	GlWindow::GlWindow(int w, int h)
	{
		m_width = w;
		m_height = h;
		m_ratio = m_width / static_cast<float>(m_height);
		setupBuffer();
	}

	/// <summary>
	/// ?Ҹ???
	/// </summary>
	GlWindow::~GlWindow() {

		delete m_grid;
		delete m_cylinder;
	}

	void GlWindow::setupBuffer()
	{
		m_grid = new grid();
		m_cylinder = new cylinder();
		m_animatedModel = new AnimatedModel();


		agentNum = SystemInfo::instance().agentAmount;
		for (int i = 0; i < agentNum; i++) {
			glm::vec2 initialPos(0.0f, i*10.0f);
			glm::vec2 goalPos(50.0f, i * 10.0f);
			agent.push_back(new SiAgent(0, initialPos));
			agent[i]->addGoalPos(goalPos);
		}
	}

	void GlWindow::setSize(int width, int height) {
		m_width = width;
		m_height = height;
	}

	void GlWindow::setAspect(float ratio) {
		m_ratio = ratio;
	}

	grid* GlWindow::getSelectedObj() {
		return m_grid;
	}

	void GlWindow::update() {
		m_grid->setup();
	}

	void GlWindow::draw(camera cam, float zoom,float _deltaTime, float animationTime)
	{
		glClearColor(0.5f, 0.5f, 0.5f, 0);		//background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//clear up color and depth buffer

		glEnable(GL_CLIP_DISTANCE0);

		glEnable(GL_DEPTH_TEST);			//test whether an object is in front of other object?
		//glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glViewport(200, 0, m_width, m_height);

		glm::mat4 viewMat = cam.GetViewMatrix();

		glm::mat4 projection = glm::perspective(glm::radians(zoom), m_ratio, 0.1f, 1000.0f);

		glm::mat4 model;
		m_model.glPushMatrix();
		model = m_model.getMatrix();
		//rect->draw(model, viewMat, projection);
		glm::mat4 offset;

		glm::mat4 origin = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f, 0.0f));
		
		m_grid->draw(model, viewMat, projection);

		m_model.glRotate(90, 1, 0,0);
		model = m_model.getMatrix();
		for (int i = 0; i < agent.size(); i++) {
			agent[i]->doStep(_deltaTime);
			offset = agent[i]->getPosition();
			m_cylinder->draw(model, viewMat, projection, offset, 0);
		}
		

		m_model.glScale(0.05f, 0.05f, 0.05f);
		model = m_model.getMatrix();
		m_animatedModel->drawMesh(model, viewMat, projection,cam.Position,animationTime,0,1,1);

		m_model.glPopMatrix();
	}

