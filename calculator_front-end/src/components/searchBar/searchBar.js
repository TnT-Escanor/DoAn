import React, { Component } from 'react';
import { Input } from 'antd';
import "./searchBar.css";

const { Search } = Input;

class SearchBar extends Component {
    constructor() {
        super();
        this.state = {

        };
    }

    render() {
        const {
            handleSearch,
          } = this.props;

        return(
            <>
                <Search
                    placeholder="Nhập mẫu cần tránh, mẫu vincular thì phần vincular để trong dấu (). Ví dụ : 1(22)"
                    allowClear
                    enterButton="Tìm kiếm"
                    size="large"
                    onSearch={value => handleSearch(value)}
                />
            </>
        );
    }
}

export default SearchBar;
