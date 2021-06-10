import React, { FunctionComponent } from "react";
import BasicLayout from "../BasicLayout/BasicLayout";
import Danger from "../../assets/img/dry.png";
import Text from "../../assets/svg/dry.svg";
import { Image, StyledText } from "./Dry.sc";

const Dry: FunctionComponent = () => {
    return (
        <BasicLayout>
            <StyledText src={Text} />
            <Image src={Danger} />
        </BasicLayout>
    )
}

export default Dry;