import React, { FunctionComponent } from "react";
import BasicLayout from "../BasicLayout/BasicLayout";
import Knight from "../../assets/img/knight_sword.png";
import Text from "../../assets/svg/attack.svg";
import { Image, StyledButton, StyledText } from "./Attack.sc";
import { Redirect, useParams } from "react-router";

const checkSlug = (slug: string) => {
    if (slug === "dry" || slug === "safe" || slug === "dark")
    {
        return true;
    }

    return false;
}

const Attack: FunctionComponent = () => {
    const {slug} = useParams<{slug: string}>();
    
    if (!checkSlug(slug)) {
        return <Redirect to="/" />;
    }

    const action = `/${slug}`;

    return (
        <BasicLayout>
            <StyledText src={Text} />
            <StyledButton to={action} type="next" />
            <Image src={Knight} />
        </BasicLayout>
    )
}

export default Attack;
