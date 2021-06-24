import React, { FunctionComponent } from "react";
import Title from "../../components/Title/Title";
import BasicLayout from "../BasicLayout/BasicLayout";
import { Image } from "./Welcome.sc";
import Knight from "../../assets/img/knight.png";
import Button from "../../components/Button/Button";

const Welcome: FunctionComponent = () => {
    return (
        <BasicLayout>
            <Title marginTop="50.6px" marginBottom="120px" />
            <Button to="/tutorial" type="welcome" />
            <Image src={Knight} />
        </BasicLayout>
    );
};

export default Welcome;
