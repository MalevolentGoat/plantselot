import styled from "styled-components";

interface LogoProps {
    marginBottom?: string;
    marginTop?: string;
}

export const Logo = styled.img<LogoProps>`
    margin-left: auto;
    margin-right: auto;
    margin-top: ${(props) => props.marginTop };
    margin-bottom: ${(props) => props.marginBottom };
    width: 260px;
`;