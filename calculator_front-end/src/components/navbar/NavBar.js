import React, { Component } from 'react';
import { Menu } from 'antd';
// import { Link } from "react-router-dom";

import {
	DingtalkOutlined
} from '@ant-design/icons';
import './NavBar.css';

class NavBar extends Component {
	render() {
		return (
			<div>
				<Menu theme="light" selectedKeys={[]} mode="horizontal" style={{ position: 'fixed', zIndex: 1, width: '100%', height: 50, background: "#FFDAB9" }}>
					<Menu.Item key="index"><a href="/"><DingtalkOutlined />Search</a></Menu.Item>
				</Menu>
			</div>
			
		);
	}
}
export default NavBar;

