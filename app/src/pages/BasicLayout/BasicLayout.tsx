import React, { FunctionComponent, ReactNode } from "react";
// import GlobalStyle from "../../GlobalStyles";
import { BasicLayoutContainer } from "./BasicLayout.sc";

interface Props {
    children?: ReactNode;
}

const BasicLayout: FunctionComponent<Props> = ({ children }) => {
    return (
        // <GlobalStyle>
            <BasicLayoutContainer>
                {children}
            </BasicLayoutContainer>
        // </GlobalStyle>
    );
};

export default BasicLayout;
