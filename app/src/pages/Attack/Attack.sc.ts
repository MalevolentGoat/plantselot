import styled from "styled-components";
import Button from "../../components/Button/Button";

export const Image = styled.img`
    position: absolute;
    bottom: 0;
    top: 0;
    right: 0;
    left: 0;
    width: 542px;
    margin-top: 335px;
    margin-left: -114px;
`;

export const StyledText = styled.img`
    width: 243px;
    margin-left: 43px;
    margin-right: auto;
    margin-top: 100px;
    margin-bottom: 83px;
`;

export const StyledButton = styled(Button)`
    && {
        background: red;
    }
`;
