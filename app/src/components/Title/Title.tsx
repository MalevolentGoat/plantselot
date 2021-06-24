import React, { FunctionComponent } from "react";
import { Logo } from "./Title.sc";
import PlantaLot from "../../assets/svg/title.svg";

interface TitleProps {
    marginTop?: string;
    marginBottom?: string;
}

const Title: FunctionComponent<TitleProps> = ({ marginTop, marginBottom }) => {
    return (
        <>
            <Logo src={PlantaLot} marginTop={marginTop} marginBottom={marginBottom} />
        </>
    );
};

export default Title;
