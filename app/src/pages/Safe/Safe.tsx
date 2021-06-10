import React, { FunctionComponent } from "react";
import BasicLayout from "../BasicLayout/BasicLayout";
import Danger from "../../assets/img/safe.svg";
import Text from "../../assets/svg/safe.svg";
import { Image, StyledText } from "./Safe.sc";

const Safe: FunctionComponent = () => {
    return (
        <BasicLayout>
            <StyledText src={Text} />
            <Image src={Danger} />
        </BasicLayout>
    );
}

export default Safe;