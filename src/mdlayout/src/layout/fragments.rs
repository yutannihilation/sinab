use super::*;
use crate::graphics_engine::shaped_segment::ShapedSegment;

#[derive(Debug)]
pub(crate) enum Fragment {
    Box(BoxFragment),
    Anonymous(AnonymousFragment),
    Text(TextFragment),
}

// debug trait explicitly implmented to prevent printing of all children
pub(crate) struct BoxFragment {
    pub style: Arc<ComputedValues>,
    pub children: Vec<Fragment>,

    /// From the containing block’s start corner…?
    /// This might be broken when the containing block is in a different writing mode:
    /// https://drafts.csswg.org/css-writing-modes/#orthogonal-flows
    pub content_rect: Rect<Length>,

    pub padding: Sides<Length>,
    pub border: Sides<Length>,
    pub margin: Sides<Length>,

    pub block_margins_collapsed_with_children: CollapsedBlockMargins,
}

#[derive(Debug)]
pub(crate) struct CollapsedBlockMargins {
    pub collapsed_through: bool,
    pub start: CollapsedMargin,
    pub end: CollapsedMargin,
}

#[derive(Copy, Clone, Debug)]
pub(crate) struct CollapsedMargin {
    max_positive: Length,
    min_negative: Length,
}

/// Can contain child fragments with relative coordinates, but does not contribute to painting itself.
// debug trait explicitly implmented to prevent printing of all children
pub(crate) struct AnonymousFragment {
    pub rect: Rect<Length>,
    pub children: Vec<Fragment>,
    pub mode: (WritingMode, Direction),
}

#[derive(Debug)]
pub(crate) struct TextFragment {
    pub parent_style: Arc<ComputedValues>,
    pub content_rect: Rect<Length>,
    pub text: ShapedSegment,
}

impl AnonymousFragment {
    pub fn no_op(mode: (WritingMode, Direction)) -> Self {
        Self {
            children: vec![],
            rect: Rect::zero(),
            mode,
        }
    }
}

impl BoxFragment {
    pub fn border_rect(&self) -> Rect<Length> {
        self.content_rect
            .inflate(&self.padding)
            .inflate(&self.border)
    }
}

impl std::fmt::Debug for BoxFragment {
    fn fmt(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(
            fmt,
            "BoxFragment {{ style: {:?}, children: {}, content_rect: {:?}, padding: {:?},
    pub border: {:?}, margin: {:?}, block_margins_collapsed_with_children: {:?} }}",
            self.style,
            self.children.len(),
            self.content_rect,
            self.padding,
            self.border,
            self.margin,
            self.block_margins_collapsed_with_children
        )
    }
}

impl std::fmt::Debug for AnonymousFragment {
    fn fmt(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(
            fmt,
            "AnonymousFragment {{ rect: {:?}, children: {}, mode: {:?} }}",
            self.rect,
            self.children.len(),
            self.mode,
        )
    }
}


impl CollapsedBlockMargins {
    pub fn from_margin(margin: &Sides<Length>) -> Self {
        Self {
            collapsed_through: false,
            start: CollapsedMargin::new(margin.block_start),
            end: CollapsedMargin::new(margin.block_end),
        }
    }

    pub fn zero() -> Self {
        Self {
            collapsed_through: false,
            start: CollapsedMargin::zero(),
            end: CollapsedMargin::zero(),
        }
    }
}

impl CollapsedMargin {
    pub fn zero() -> Self {
        Self {
            max_positive: Length::zero(),
            min_negative: Length::zero(),
        }
    }

    pub fn new(margin: Length) -> Self {
        Self {
            max_positive: margin.max(Length::zero()),
            min_negative: margin.min(Length::zero()),
        }
    }

    pub fn adjoin(&self, other: &Self) -> Self {
        Self {
            max_positive: self.max_positive.max(other.max_positive),
            min_negative: self.min_negative.min(other.min_negative),
        }
    }

    pub fn adjoin_assign(&mut self, other: &Self) {
        *self = self.adjoin(other);
    }

    pub fn solve(&self) -> Length {
        self.max_positive + self.min_negative
    }
}