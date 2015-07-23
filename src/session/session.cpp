#include "session.hpp"


session::session(socket_ctrl& ctrl, config& cfg)
	: m_ctrl{ctrl}
	, m_cfg{cfg}
{
	m_ctrl.send(m_cfg.get_opt("issue"));
}


session::~session()
{
	delete &m_ctrl;
}
