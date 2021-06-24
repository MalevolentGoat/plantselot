import React, { FunctionComponent } from "react";
import BasicLayout from "../BasicLayout/BasicLayout";
import Dark from "../../assets/img/dark.png";
import Text from "../../assets/svg/danger_dark.svg";
import { Image, StyledText } from "./Danger.sc";

const Danger: FunctionComponent = () => {
    return (
        <BasicLayout>
            <StyledText src={Text} />
            <Image src={Dark} />
        </BasicLayout>
    )
}

export default Danger;
