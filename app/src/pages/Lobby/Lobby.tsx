import React, { FunctionComponent } from "react";
import Title from "../../components/Title/Title";
import BasicLayout from "../BasicLayout/BasicLayout";
import { Image, StyledText } from "./Lobby.sc";
import Knight from "../../assets/img/knight_lobby.png";
import Text from "../../assets/svg/pepare_battle.svg";
import Button from "../../components/Button/Button";

const Lobby: FunctionComponent = () => {
    return (
        <BasicLayout>
            <Title marginTop="94px" />
            <Image src={Knight} />
            <StyledText src={Text} />
            <Button to="/tutorial" type="next" />
        </BasicLayout>
    )
}

export default Lobby;
