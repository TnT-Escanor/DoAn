import React from "react";
// import AddTag from "./components/addTag";
import NavBar from "../../components/navbar/NavBar";
import "./Page.css";
import { Layout, Checkbox, Button, Row, Col, InputNumber, Tabs } from 'antd';
import SearchBar from "../../components/searchBar/searchBar"
// import Api from "../../routes/Api"


const { Content, Footer } = Layout;
const { TabPane } = Tabs;
const style = { background: '#C0C0C0', padding: '4px', textAlign: 'center', marginLeft: '-20px' };

class Page extends React.Component {
    constructor() {
        super();
        this.state = {
            userInfo: {
                name: "TNT",
            },
            screenWidth: window.innerWidth,
            screenHeight: window.innerHeight,
            string: '',
            num: '5',
            checked: true,
            check: '',
            checkString: false,
            disabled: false,
            result: '',
            numberIdx: 0,
            listResult: [],
            tabPosition: "1",
        };
    }

    handleSearch = value => {
        if (value !== "") {
            if (this.state.checked === true) { this.state.check = 1 }
            else { this.state.check = 0 }
            let i = 0;
            let errorS = 0;
            let count = 0;
            let countS = 0;
            for (i; i < value.length; i++) {
                if(count >1 || countS > 1 || count < 0) errorS =1;
                if (value[i] !== "0" && value[i] !== "1" && value[i] !== "2" && value[i] !== "3" && value[i] !== "4" && value[i] !== "5" && value[i] !== "6" && value[i] !== "7" && value[i] !== "8" && value[i] !== "9" && value[i] !== "(" && value[i] !== ")" && value[i] !== ",") {
                    errorS = 1;
                }
                else if (value[i] === "(") {
                    count ++;
                    countS ++;
                }
                else if (value[i] === ")") {
                    count--;
                    if(value[i-1] === "(") errorS = 1;
                }
                else if (value[i] === "," && count !== 0) errorS = 1;
                else if (value[i] === "," && i === value.length - 1) errorS = 1;
                else if (value[i] === ",") {
                    countS = 0;
                    if (value[i-1] === ",") errorS = 1;
                }
            }
            if (errorS === 1 || count > 0) {
                console.log("errors");
            }
            else {
                if (this.state.tabPosition === "1") {
                    this.props.Api.calculate(
                        this.state.num,
                        this.state.check,
                        value,
                        (result) => {
                            this.setResult(result);
                        });
                }
                else if (this.state.tabPosition === "2") {
                    this.props.Api.calculate(
                        0,
                        this.state.check,
                        value,
                        (result) => {
                            this.setResult(result);
                        });
                }
            }
        }
        else return
    }

    setResult(result) {
        const newNumbers = [result, ""];
        const newNumberIdx = 0;
        this.setState({ listResult: [] })
        let listComma = [];
        this.setState({
            result: newNumbers[newNumberIdx],
            numbers: newNumbers,
            numberIdx: newNumberIdx,
        });
        if (this.state.result === []) { }
        else {
            let i = 0;
            let length = this.state.result.length;
            for (i; i < length; i++) {
                if (this.state.result[i] === ";") {
                    listComma.push(i);
                }
            }
        }
        console.log(listComma);
        console.log(this.state.result.type);
        this.state.listResult.push(this.state.result.slice(0, listComma[0]))
        let a = 0;
        for (a = 0; a < listComma.length - 1; a++) {
            let b = this.state.result.slice(listComma[a] + 1, listComma[a + 1]);
            this.state.listResult.push(b)
            // console.log(listResult, "chuoi gia tri da tach")
        }
        this.setState({ iscompleted: true })
    }

    renderListResult = (data) => {
        let renderListResult = data;
        if (this.state.tabPosition === "1") {
            return (data ? renderListResult.map((post, index) => (
                <Col span={3} offset={1} key={index}>
                    <p style={style} >{post}</p>
                </Col>
            ))
                : (<Col><h2></h2></Col>)
            );
        }
        else if (this.state.tabPosition === "2") {
            return (data ? renderListResult.map((post, index) => (
                <Col span={5} offset={1} key={index} value={post} >
                    <Button size="large" target='_blank' href={"http://oeis.org/" + post} style={{ textAlign: "center", marginTop: "1em" }}>
                        {post}
                    </Button>
                </Col>
            ))
                : (<Col><h2></h2></Col>)
            );
        }
    };

    updateScreenSize = () => {
        this.setState({ screenWidth: window.innerWidth, screenHeight: window.innerHeight })
    }

    changeTabPosition = e => {
        this.setState({
            tabPosition: e,
            listResult: "",
        });
    };

    toggleChecked = () => {
        this.setState({ checked: !this.state.checked });
    };

    onChange = e => {
        this.setState({
            checked: e.target.checked,
        });
    };

    changeLength = value => {
        this.setState({
            num: value,
        });
        console.log(value)
    }


    render() {
        console.log(this.state.checked);
        console.log(this.state.string);
        console.log(this.state.result)
        return (
            <Layout className="layout" style={{ background: "#fff" }}>
                <NavBar
                    currentPage={this.state.currentPage}
                    onClickChangePage={this.onClickChangePage}
                />
                <Content style={{ width: "100%", padding: '0 200px', margin: "auto", minHeight: '90vh' }}>
                    <Tabs defaultActiveKey={this.state.tabPosition} style={{ fontSize: "1.3em", marginTop: "2.5em" }} size="large" onChange={e => this.changeTabPosition(e)} centered>
                        <TabPane tab="Danh sách các RGF tránh mẫu" key="1">
                            <div className="site-layout-content">
                                <div className="search-bar" style={{
                                    width: "70%",
                                    margin: "auto",
                                    marginBottom: "0em",
                                    marginTop: "-1.3em",
                                    zIndex: "99999",
                                    textAlign: "center",
                                }}>
                                    <SearchBar
                                        value={this.state.string}
                                        handleSearch={this.handleSearch}

                                    >
                                    </SearchBar>

                                </div>

                                <div style={{
                                    width: "70%",
                                    margin: "auto",
                                    marginBottom: "2em",
                                    marginTop: '0em',
                                    zIndex: "99999",
                                }}>
                                    <div style={{ marginBottom: '20px' }}>
                                        <Checkbox
                                            checked={this.state.checked}
                                            onChange={this.onChange}
                                        >
                                        </Checkbox>
                                        <Button style={{ margin: '10px' }} type="primary" size="normal" onClick={this.toggleChecked}>
                                            {!this.state.checked ? 'Permutation' : 'RGF'}
                                        </Button>
                                        <InputNumber style={{ marginLeft: '20px' }} min={1} max={10} value={this.state.num} bordered={false} onChange={this.changeLength} />

                                    </div>

                                </div>

                                <div style={{
                                    width: "50%",
                                    margin: "auto",
                                    marginBottom: "2em",
                                    marginTop: '-1.5em',
                                    zIndex: "99999",

                                }}>
                                    <Row> {this.renderListResult(this.state.listResult)}</Row>

                                </div>

                            </div>
                        </TabPane>
                        <TabPane tab="Kiểm tra lực lượng qua oeis" key="2">
                            <div className="site-layout-content">
                                <div className="search-bar" style={{
                                    width: "70%",
                                    margin: "auto",
                                    marginBottom: "0em",
                                    marginTop: "-1.3em",
                                    zIndex: "99999",
                                    textAlign: "center",
                                }}>
                                    <SearchBar
                                        value={this.state.string}
                                        handleSearch={this.handleSearch}

                                    >
                                    </SearchBar>

                                </div>

                                <div style={{
                                    width: "70%",
                                    margin: "auto",
                                    marginBottom: "2em",
                                    marginTop: '0em',
                                    zIndex: "99999",
                                }}>
                                    <div style={{ marginBottom: '20px' }}>
                                        <Checkbox
                                            checked={this.state.checked}
                                            onChange={this.onChange}
                                        >
                                        </Checkbox>
                                        <Button style={{ margin: '10px' }} type="primary" size="normal" onClick={this.toggleChecked}>
                                            {!this.state.checked ? 'Permutation' : 'RGF'}
                                        </Button>

                                    </div>

                                </div>

                                <div style={{
                                    width: "50%",
                                    margin: "auto",
                                    marginBottom: "2em",
                                    marginTop: '-1.5em',
                                    zIndex: "99999",
                                    left: "25%"
                                }}>
                                    <Row> {this.renderListResult(this.state.listResult)}</Row>
                                </div>
                            </div>
                        </TabPane>
                    </Tabs>
                </Content>
                <Footer style={{
                    textAlign: "center",
                }}>Nguyễn Anh Đức</Footer>
            </Layout>
        );
    }
}

export default Page;
