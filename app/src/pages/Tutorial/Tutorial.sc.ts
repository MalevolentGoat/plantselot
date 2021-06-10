import styled from "styled-components";

interface ImageProps {
    marginBottom?: string;
    marginTop?: string;
    width?: string;
}

export const Image = styled.img<ImageProps>`
    width: ${(props) => props.width};
    margin-top: ${(props) => props.marginTop };
    margin-bottom: ${(props) => props.marginBottom };
    margin-left: auto;
    margin-right: auto;
`;

export const Background = styled.img`
    position: absolute;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    width: 95%;
    margin-left: auto;
    margin-right: auto;
    margin-top: auto;
    margin-bottom: 50px;
    opacity: 0.3;
`;
