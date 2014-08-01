#include "Camera.h"


Camera::Camera() {

}
Camera::~Camera() {

}

uint_32	Camera::get_camera_x() {
	return m_x;
}

uint_32 Camera::get_camera_y() {
	return m_y;
}

uint_32 Camera::get_camera_width() {
	return	m_width;
}

uint_32 Camera::get_camera_height() {
	return m_height;
}

RECT  Camera::get_camera_rect() {
	RECT			_rect;

	_rect.left	 = m_x;
	_rect.top	 = m_y;
	_rect.right	 = m_x + m_width;
	_rect.bottom = m_y + m_height;

	return _rect;
}


void Camera::set_camera_x(const uint_32 & _x) {
	m_x = _x;
}

void Camera::set_camera_y(const uint_32 & _y) {
	m_y = _y;
}

void Camera::set_camera_width(const uint_32 & _width) {
	m_width = _width;
}

void Camera::set_camera_height(const uint_32 & _height) {
	m_height = _height;
}


void Camera::move_camera_v(const int_32 & _dx) {
	m_x += _dx;
}

void Camera::move_camera_h(const int_32 & _dy) {
	m_y += _dy;
}