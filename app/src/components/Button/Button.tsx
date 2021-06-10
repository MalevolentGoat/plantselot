import React, { FunctionComponent } from "react";
import { StyledButton } from "./Button.sc";
import Welcome from "../../assets/img/welcome.png";
import Next from "../../assets/img/next.svg";

interface ButtonProps {
    to: string;
    type: string;
}

const Button: FunctionComponent<ButtonProps> = ({ to, type }) => {
    return (
        <StyledButton to={to}>
            {type === "welcome" && (
                <img src={Welcome} />
            )}
            {type === "next" && (
                <img src={Next} />
            )}
        </StyledButton>
    );
};

export default Button;
