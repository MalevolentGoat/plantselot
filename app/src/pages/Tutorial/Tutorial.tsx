import React, { FunctionComponent } from "react";
import Title from "../../components/Title/Title";
import BasicLayout from "../BasicLayout/BasicLayout";
import Setup from "../../assets/svg/setup.svg";
import Text from "../../assets/svg/tutorial.svg";
import Knight from "../../assets/img/knight.png";
import { Background, Image } from "./Tutorial.sc";

const Tutorial: FunctionComponent = () => {
    return (
        <BasicLayout>
            <Background src={Knight} />
            <Title marginTop="100px" marginBottom="25px" />
            <Image width="100px" src={Setup} />
            <Image width="80%" src={Text} marginTop="50px" />
        </BasicLayout>
    );
};

export default Tutorial;
