import React from 'react';
import { Switch, Route } from 'react-router-dom';
import Page from "../views/content/Page";
import Api from "./Api"

const Routes = () => (
    <Switch>
        <Route path='/'>
            <Page Api = {new Api('http://127.0.0.1:8080')} />
        </Route>
    </Switch>
);

export default Routes;
